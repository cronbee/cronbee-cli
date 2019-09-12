//
// Created by Pierre on 8/28/19.
//

#ifndef CRONBEE_CRONBEE_H
#define CRONBEE_CRONBEE_H

#include <curl/curl.h>
#include <curl/easy.h>
#include "main.h"

#define _URL_ "https://api.cronbee.com"
struct curl_data {
    size_t size;
    char* response;
    bool success;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, struct curl_data *data);
bool cronbee_ping(char*, struct options *);
bool cronbee_start(struct options*);
bool cronbee_event(struct options *, char*);
bool cronbee_stop(struct options*);
void sendMessage(char*, struct curl_data*);
#endif //CRONBEE_CRONBEE_H
