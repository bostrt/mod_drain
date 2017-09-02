FROM fedora:latest

RUN dnf install -y git gcc httpd httpd-devel redhat-rpm-config && \
    dnf clean all

RUN git clone https://github.com/bostrt/mod_drain.git && \
    cd mod_drain && \
    apxs -i -c mod_drain.c

COPY drain.conf /etc/httpd/conf.d/drain.conf

EXPOSE 80

CMD ["httpd", "-DFOREGROUND"]
