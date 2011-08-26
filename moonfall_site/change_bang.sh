#!/bin/bash

perl -p -i -e \
"s%#!/usr/bin/env moonfall%#!/usr/bin/env /home/moonfall/moonfall%" \
moonfall.cgi