#!/bin/bash

MY_DASM="./dasm"
MY_ASM="./asm"

if [ -z "$1" ] ; then
	echo "Usage: dasm_comparator.sh dirname"
	exit 1
fi

if [ ! -f "$MY_DASM" ]; then
	echo "File $MY_DASM does not exist"
	exit 1
fi

if [ ! -f "$MY_ASM" ]; then
	echo "File $MY_ASM does not exist"
	exit 1
fi

GREEN="\e[32m"
RED="\e[31m"
YELLOW="\e[1;33m"
EOC="\e[0m"

for S_FILE in $( find ${1} -type f -name "*.s" ); do

	COR_FILE="${S_FILE%".s"}.cor"

	MY_S="champ.s"
	MY_COR="champ.cor"

	${MY_ASM} ${S_FILE} &>/dev/null
	if [[ -e ${COR_FILE} ]]; then
		cp ${COR_FILE} ${MY_COR}
	fi

	${MY_DASM} ${MY_COR} &>/dev/null
	${MY_ASM} ${MY_S} &>/dev/null

	if [[ -e ${MY_COR} ]] && [[ -e ${COR_FILE} ]]; then
		if diff ${MY_COR} ${COR_FILE} &>/dev/null;
			then printf "${GREEN}OK${EOC}\t${COR_FILE}\n"
			else printf "${RED}KO${EOC}\t${COR_FILE}\n"
		fi
		rm ${COR_FILE} ${MY_COR} ${MY_S}
	elif [[ -e ${MY_COR} ]]; then
		printf "${YELLOW}ERROR${EOC}\t(${MY_COR} was not created)\n"
		rm ${MY_S} ;
	elif [[ -e ${MY_S} ]]; then
		printf "${YELLOW}ERROR${EOC}\t(${MY_S} was not created)\n"
		rm ${MY_COR}
	else
		printf "${YELLOW}ERROR${EOC}\t(incorrect file) ${S_FILE}\n"
	fi
done
