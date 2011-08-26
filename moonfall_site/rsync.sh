#!/bin/bash -x

USER=moonfall
DOMAIN=moonfall.org

rsync -avz . \
${USER}@${DOMAIN}:${DOMAIN} \
--delete \
--exclude '.svn'


ssh ${USER}@${DOMAIN} "cd ${DOMAIN}; ./change_bang.sh"

