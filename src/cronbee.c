//
// Created by Pierre on 8/28/19.
//

#include "../include/cronbee.h"

void sendMessage(char* message, struct curl_data *response) {
    long responseCode = -1;

    void* curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, message);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        CURLcode curlCode = curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);

        if (curlCode == CURLE_OK) {
            response->success = true;
        }
        if (curlCode != CURLE_OK) {
            response->success = false;
            printError(curl_easy_strerror(curlCode));
        }

        if(responseCode != 200) {
            printError(response->response);
        }

        curl_easy_cleanup(curl);
    }
}

size_t write_data(void *ptr, size_t size, size_t nmemb, struct curl_data *data) {
    size_t written = data->size;
    size_t n = size * nmemb;
    data->size += (size * nmemb);
    char *tmp = realloc(data->response, data->size + 1);
    if(tmp) {
        data->response = tmp;
    }
    else {
        if(data->response) {
            free(data->response);
            printError("Unable to allocate memory\n");
        }
        exit(EXIT_FAILURE);
    }

    memcpy((data->response + written), ptr, n);
    data->response[data->size] = '\0';
    return size * nmemb;
}

bool cronbee_ping(char* monitorId, struct options *options) {
    struct curl_data response = {0, calloc(1, sizeof(char)), false};
    char* msg = calloc(strlen(_URL_) + strlen("/monitor/") + strlen(monitorId) + strlen("/ping") + 1 , sizeof(char));
    strcpy(msg, _URL_);
    strcat(msg, "/monitor/");
    strcat(msg, monitorId);
    strcat(msg, "/ping");
    printInfo(msg, options);
    sendMessage(msg, &response);
    free(msg);
    return response.success;
}

bool cronbee_start(struct options *options) {
    struct curl_data response = {0, calloc(1, sizeof(char)), false};
    char* msg = calloc(strlen(_URL_) + strlen("/monitor/") + strlen(options->uuid) + 1 , sizeof(char));
    strcpy(msg, _URL_);
    strcat(msg, "/monitor/");
    strcat(msg, options->uuid);
    printInfo(msg, options);
    sendMessage(msg, &response);
    options->token = response.response;
    free(msg);
    setEnvVar("CRONBEE_TOKEN", options->token);
    return response.success;
}

bool cronbee_stop(struct options *options) {
    return cronbee_event(options, "stop");
}

bool cronbee_event(struct options *options, char* event) {
    struct curl_data response = {0, calloc(1, sizeof(char)), false};
    char* msg = calloc(strlen(_URL_)
            + strlen("/monitor/")
            + strlen(options->uuid)
            + strlen("/event/")
            + strlen(event)
            + strlen("?token=")
            + strlen(options->token) + 1 , sizeof(char));
    strcpy(msg, _URL_);
    strcat(msg, "/monitor/");
    strcat(msg, options->uuid);
    strcat(msg, "/event/");
    strcat(msg, event);
    strcat(msg, "?token=");
    strcat(msg, options->token);
    printInfo(msg, options);
    sendMessage(msg, &response);
    free(msg);
    return response.success;
}
