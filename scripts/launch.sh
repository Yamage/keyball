##!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

if [[ "${1-}" =~ ^-*h(elp)?$ ]]; then
    echo 'Usage: ./build.sh []
TODO
'
    exit
fi

cd "$(dirname "$0")"

main() {
	CURRENT_DIR=$(pwd)
	BASEFILE=$(readlink -f $0)
	SCRIPT_DIR=$(dirname $BASEFILE)
	QMK_KEYBOARDS_KEYBALL_DIR="$(cd ${SCRIPT_DIR%/}/../qmk_firmware/keyboards/keyball; pwd)"

	cd $SCRIPT_DIR
	. ./.env.local


	DOCKER_CONTAINER_NAME='qmkfm/qmk_cli'

	cd $QMK_HOME
	docker build . -t $DOCKER_CONTAINER_NAME

	echo "Launch: $BUILD_TARGET"
	docker run -it --rm --tty \
		-v $QMK_HOME:/qmk_firmware \
		-v $QMK_KEYBOARDS_KEYBALL_DIR:/qmk_firmware/keyboards/keyball \
 	       $DOCKER_CONTAINER_NAME \
		/bin/bash 
}

main "$@"

