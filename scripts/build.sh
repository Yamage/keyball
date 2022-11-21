##!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail
if [[ "${TRACE-0}" == "1" ]]; then
    set -o xtrace
fi

if [[ "${1-}" =~ ^-*h(elp)?$ ]]; then
    echo 'Usage: ./build.sh []
todo: add help
'
    exit
fi

cd "$(dirname "$0")"

TARGET_KEYBOARD="${1:-keyball/keyball39custom}"
TARGET_KEYBOARD_FAMILY="${TARGET_KEYBOARD%/*}"
TARGET_KEYBOARD_KEYMAP="${2:-via}"

main() {
	CURRENT_DIR=$(pwd)
	BASEFILE=$(readlink -f $0)
	SCRIPT_DIR=$(dirname $BASEFILE)
	DIST_DIR=$(cd $SCRIPT_DIR && cd ../ && echo $PWD/dist)
	QMK_KEYBOARDS_DIR="$(cd ${SCRIPT_DIR%/}/../qmk_firmware/keyboards/${TARGET_KEYBOARD_FAMILY}; pwd)"

	echo "Keyboad: ${TARGET_KEYBOARD}"
	echo "Keyboad Familly: ${TARGET_KEYBOARD_FAMILY}"
	echo "Keyboad Keymap: ${TARGET_KEYBOARD_KEYMAP}"

	cd $SCRIPT_DIR
	. ./.env.local


	DOCKER_CONTAINER_NAME='qmkfm/qmk_cli'

	cd $QMK_HOME
	docker build . -t $DOCKER_CONTAINER_NAME

	BUILD_TARGET=${TARGET_KEYBOARD}:${TARGET_KEYBOARD_KEYMAP}
	echo "Build: $BUILD_TARGET"
	docker run -it --rm \
		-v $QMK_HOME:/qmk_firmware \
		-v $QMK_KEYBOARDS_DIR:/qmk_firmware/keyboards/${TARGET_KEYBOARD_FAMILY} \
        $DOCKER_CONTAINER_NAME \
		/bin/bash -lc "cd /qmk_firmware && make -B $BUILD_TARGET"

	echo 'BUILD DONE'

	mkdir -p $DIST_DIR
	BUILD_TARGET_TMP=${BUILD_TARGET//\//_}
	BUILD_TARGET_TMP=${BUILD_TARGET_TMP//:/_}
	mv -f ${BUILD_TARGET_TMP}.hex $DIST_DIR || true
	mv -f ${BUILD_TARGET_TMP}.uf2 $DIST_DIR || true

	echo "MOVE Firmware to Dist: ${DIST_DIR}"
}


main "$@"
