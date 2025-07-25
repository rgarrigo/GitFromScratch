FROM alpine

RUN apk update \
	&& apk upgrade \
	&& apk add openssh bash git file gcc musl-dev make mandoc man-pages

COPY git /usr/local/git
COPY resources/mail /usr/local/mail
COPY resources/man /usr/local/man
COPY resources/motd /etc/motd
COPY scripts /usr/local/scripts
COPY entrypoint.sh /root/entrypoint.sh

EXPOSE 22

ENTRYPOINT ["sh", "/root/entrypoint.sh"]
