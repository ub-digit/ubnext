FROM alpine:latest AS release
RUN apk add --no-cache git

ARG GIT_REVISION
ARG GIT_REPO_URL

WORKDIR /root/

RUN set -ex \
  && git clone $GIT_REPO_URL release -b $GIT_REVISION --depth 1

FROM docker.ub.gu.se/solr-5.5.5:v1

WORKDIR /opt/solr/server/solr/ubnext

COPY --from=release /root/release/etc/solr-conf/core.properties ./
COPY --from=release /root/release/etc/solr-conf/5.x ./conf
