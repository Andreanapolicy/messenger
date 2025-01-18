#!/usr/bin/env bash

set -o errexit

cd "$(dirname "$0")"/..

SSH_DIR=${HOME}/.ssh
USER_ID=$(id -u)
DOCKER_GROUP_ID=$(cut -d: -f3 < <(getent group docker))
SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
APP_DIR=$(dirname "$SCRIPT_DIR")

docker build -t messenger-app -f docker/Dockerfile .
docker run --rm --user "$USER_ID:$DOCKER_GROUP_ID" \
    --volume "$SSH_DIR:$SSH_DIR:ro" \
    --volume "$APP_DIR:/var/www/messenger"\
    --volume /mnt/sun/Builds/ispring:/mnt/sun/Builds/ispring \
    --volume /etc/passwd:/etc/passwd:ro \
    --volume /etc/group:/etc/group:ro \
    --volume /var/run/docker.sock:/var/run/docker.sock \
    --volume "/run/user/$(id -u)/:/run/user/$(id -u)/:ro" \
    -w "/var/www/messenger" \
    --name=messenger-app messenger-app \
    ./run_build.sh