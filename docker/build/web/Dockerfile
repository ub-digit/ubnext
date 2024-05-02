FROM node:8.12-alpine AS release
RUN apk add --no-cache git

ARG GIT_REVISION
ARG GIT_REPO_URL

WORKDIR /root/

RUN set -ex \
  && git clone $GIT_REPO_URL release -b $GIT_REVISION --depth 1

WORKDIR /root/release/web/sites/default/themes/ubnext
RUN npm install && ./node_modules/grunt-cli/bin/grunt less

FROM httpd:2-alpine

COPY --from=release /root/release/web/ /usr/local/apache2/htdocs/

RUN sed -i \
        -e 's/^#\(LoadModule .*mod_rewrite.so\)/\1/' \
        -e 's/^#\(LoadModule .*mod_proxy.so\)/\1/' \
        -e 's/^#\(LoadModule .*mod_proxy_fcgi.so\)/\1/' \
        -e 's/AllowOverride None/AllowOverride All/' \
        -e 's/Listen 80/Listen 8080/' \
        conf/httpd.conf \
    && echo "ProxyPassMatch ^/(.*\.php(/.*)?)$ fcgi://app:9000/var/www/html/$1 timeout=600"  >> conf/httpd.conf

RUN chmod -R 777 /usr/local/apache2/logs
