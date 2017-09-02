# mod_drain

`mod_drain` is an Apache HTTPD 2.4 module designed to create memory leaks. This can be used as a training tool. I am 100% sure this module isn't good for anything else.

## Building
Build `mod_drain` with the `apxs` tool shipped with your Apache HTTPD.

```
# git clone https://github.com/bostrt/mod_drain.git
# cd mod_drain
# apxs -i -c mod_drain.c
```

## Configuration
After building the module, you will need to add configuration to Apache HTTPD that loads the module and sets up the `mod_drain` handler.

For example:
```
# cat /etc/httpd/conf.d/drain.conf
LoadModule drain_module modules/mod_drain.so
<Location "/drain">
  SetHandler drain-handler
</Location>
```

## Usage

### Basic Usage
After building and configuring `mod_drain`, you can trigger it by sending a request to the location you configuration the handler at.

Below is a curl command that would work with the configuration in the section above.

```
# curl http://localhost/drain
mod_drain
10 MB drained
```

You can also change the amount of memory drained by using the `amount` request parameter.

```
# curl http://localhost/drain?amount=100
mod_drain
100 MB drained
```

### Docker Usage

A `Dockerfile` is provided in this repository so you can build a docker image to play with `mod_drain`. Run the following from inside the `mod_drain` source directory:

```
# docker built -t mod_drain .
# docker run -d -p 8080:80 mod_drain
# curl http://localhost:8080/drain
mod_drain
10 MB drained
```
