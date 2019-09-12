# Cronbee CLI

A command line interface for [Cronbee monitoring tool](https://cronbee.com).  
The easiest way to monitor your Cron tasks!

## Getting started 

1.You'll need an account at [https://cronbee.com](https://cronbee.com) to get started.  
2.In the Cronbee interface, copy your monitor ID (e.g. e6de1592-dc23-4436-b32d-79c0a47ea327)  

![](uuid.png)

## Usage
Basic usage of the command is...

```
$ cronbee -u UUID [OPTIONS] [COMMAND]
```

The CLI can be used in three ways:

### 1. Simple ping

You can signal that a cron job has run successfully completed using a ping event:

```
cronbee -u 43d483a8-6487-4428-82ec-5199d23ba22a -p
```

### 2. Wrapping a task with a start/stop event
​Running this command will signal cronbee that your script has *started* and on exit will signal a *stop* OR *error* event based on the exit code of the process:

```
cronbee -u 43d483a8-6487-4428-82ec-5199d23ba22a my-script.sh
```

### 3. Running a multi-stage workflow:

The CLI tool set automatically the token into a environment variable as CRONBEE_TOKEN who can be used into scripts like this way
```
cronbee -u 43d483a8-6487-4428-82ec-5199d23ba22a -e [EVENT] -t $CRONBEE_TOKEN
```

## CLI Options

Here are the options available in the CLI:

| Name    | Description                                        |
|-------|------------------------------------------------------|
| -e    | Set the event name to send                           |
| -h    | Display help                                         |
| -?    | Display help                                         |
| -n    | Set the default line number to display (default 200) |
| -p    | Send a ping to a monitor                             |
| -t    | Specify the token                                    |
| -u    | Specify the monitor id (required)                    |
| -v    | Display messages                                     |

## Installation

### Debian

```
$ wget -O - http://packages.cronbee.com/apt/conf/key.gpg.key|apt-key add -  
$ curl https://packages.cronbee.com/apt/debian/buster.conf > /etc/apt/sources.list.d/  
$ apt-get update
$ apt-get install cronbee
```

### Ubuntu

```
$ wget -O - http://packages.cronbee.com/apt/conf/key.gpg.key|apt-key add -  
$ curl https://packages.cronbee.com/apt/ubuntu/bionic.conf > /etc/apt/sources.list.d/  
$ apt-get update
$ apt-get install cronbee
```

### Compile from sources

#### Pre-requisites
1. [Cmake](https://github.com/Kitware/CMake)
2. [curl](https://github.com/curl/curl)
```
$ git clone https://github.com/cronbee/cronbee-cli.git
$ cmake .
$ make
```

## License
This project is licensed under the GPL-3.0 License

## Contact

You can send us a message at hello@cronbee.com