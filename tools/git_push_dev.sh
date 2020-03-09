#!/bin/bash

git add --all && \
	git commit -m $1 && \
	git push origin develop && \
	git push gitee develop
