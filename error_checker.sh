#!/usr/bin/env bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    error_checker.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/03 16:51:20 by mhaddi            #+#    #+#              #
#    Updated: 2021/07/05 03:02:52 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED='\033[0;31m'
GRN='\033[0;32m'
BLU='\033[0;34m'
LGRN='\033[1;32m'
YLW='\033[0;33m'
UNDRLN='\033[4m'
NC='\033[0m'

if [[ -z $1 ]]
then
	echo -e "No options were specified.\n"
	echo -e "-a, --all\t\tcheck errors on both push_swap and checker programs."
	echo -e "-p, --push_swap\t\tcheck errors on the push_swap program only."
	echo -e "-c, --checker\t\tcheck errors on the checker program only."
	exit 1
elif [[ ! $1 =~ ^(--all|-a|--push_swap|-p|--checker|-c)$ ]]
then
	echo -e "Invalid option $1."
	exit 1
fi

	##################################
	# Check push_swap parsing errors #
	##################################
	
if [[ $1 == "--push_swap" ]] || [[ $1 == "-p" ]] || [[ $1 == "--all" ]] || [[ $1 == "-a" ]]
then
	echo -e "${YLW}${UNDRLN}CHECKING IF PUSH_SWAP CORRECTLY HANDLES ARGUMENTS:${NC}"
	echo ""
	
	echo -e "${YLW}make${NC}"
	make re
	make # in case no rule `re` was found
	echo ""
	
	if [[ ! -f ./push_swap ]]
	then
    	echo "The push_swap binary was not found in the current directory."
		exit 1
	fi

	echo "Test:"
	echo -e "${LGRN}./push_swap '5' '6' '' '3'${NC}"
	./push_swap '5' '6' '' '3' 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "An empty argument is an error."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 5 6 \"  3  4 1  \" 0${NC}"
	./push_swap 5 6 "  3  4 1  " 0 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, if an argument has multiple numbers,"
		echo "separated by space, they are splitted into new arguments."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 5 6 \"  3  5 1  \" 0${NC}"
	./push_swap 5 6 "  3  5 1  " 0 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Number five is a duplicate."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap +-5${NC}"
	./push_swap +-5 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "A plus sign should only be followed by a number."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 00001 000${NC}"
	./push_swap 00001 000 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, trailing zeros must be stripped."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 0${NC}"
	./push_swap 0 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 000${NC}"
	./push_swap 000 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, trailing zeros must be stripped,"
		echo "until a digit is reached (in this case the digit itself is a zero),"
		echo "which is the passed argument."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 00000 0000000 ${NC}"
	./push_swap 00000 0000000 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Two zeros passed as arguments, they are duplicates."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap +001    +000${NC}"
	./push_swap +001    +000 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, the plus sign must be stripped, as well as the trailing zeros."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap +0${NC}"
	./push_swap +0 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, only the plus sign must be stripped."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 001    -+000${NC}"
	./push_swap 001    -+000 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "A minus sign should only be followed by a number."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 001    ++000${NC}"
	./push_swap 001    ++000 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "A plus sign should only be followed by a number."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap +${NC}"
	./push_swap + 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Non-numeric argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap ++${NC}"
	./push_swap ++ 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Non-numeric argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 2147483648${NC}"
	./push_swap 2147483648 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Argument is bigger than integer."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 11474836481${NC}"
	./push_swap 11474836481 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Argument is bigger than integer."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap -2147483649${NC}"
	./push_swap -2147483649 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Argument is bigger than integer."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap -11474836491${NC}"
	./push_swap -11474836491 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Argument is bigger than integer."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 2147483647${NC}"
	./push_swap 2147483647 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, 2147483647 is a valid integer."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap -2147483648${NC}"
	./push_swap -2147483648 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, -2147483648 is a valid integer."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 0000000000000000000000${NC}"
	./push_swap 0000000000000000000000 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, all trailing zeros must be stripped until a zero is left."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 0-1${NC}"
	./push_swap 0-1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 0-11${NC}"
	./push_swap 0-11 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 00-11${NC}"
	./push_swap 00-11 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 000-11${NC}"
	./push_swap 000-11 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 0+1${NC}"
	./push_swap 0+1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 0+11${NC}"
	./push_swap 0+11 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 00+11${NC}"
	./push_swap 00+11 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap 000+11${NC}"
	./push_swap 000+11 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap --1${NC}"
	./push_swap --1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not a valid argument."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap -001${NC}"
	./push_swap -001 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, all trailing zeros must be stripped."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap -01${NC}"
	./push_swap -01 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, all trailing zeros must be stripped."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap -00000000000000000000001${NC}"
	./push_swap -00000000000000000000001 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, all trailing zeros must be stripped."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap -0000000000000000000001 -1${NC}"
	./push_swap -0000000000000000000001 -1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Duplicate -1!"
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	echo "Test:"
	echo -e "${LGRN}./push_swap${NC}"
	./push_swap 1>/tmp/Output 2>/tmp/Error
	tmpExitCode=$?
	if [[ -s /tmp/Output ]] || [[ -s /tmp/Error ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "You should print nothing, neither on stdout,"
		echo "nor on stderr, nor take from stdin."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
fi
	
	############################################
	# Check some errors in the checker program #
	############################################
	
if [[ $1 == "--checker" ]] || [[ $1 == "-c" ]] || [[ $1 == "--all" ]] || [[ $1 == "-a" ]]
then
	echo -e "${YLW}${UNDRLN}CHECKING IF THE CHECKER CORRECTLY HANDLES OPERATIONS.${NC}"
	echo ""
	
	echo -e "${YLW}make bonus${NC}"
	make bonus
	echo ""
	
	if [[ ! -f ./checker ]]
	then
    	echo "The checker binary was not found in the current directory."
		exit 1
	fi

	# ./checker 1 2 3 4 5
	# EOF => OK
	
	echo "Test:"
	echo "Not passing any newline, just EOF, to a sorted argument list."
	echo -e "${LGRN}echo -n \"\" | ./checker 1 2 3 4 5${NC}"
	echo -n "" | ./checker 1 2 3 4 5 1>/tmp/Output 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]] || [[ $(cat -e /tmp/Output) == 'KO$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, nor is it a KO, list is already sorted,"
		echo "so no operation is required, EOF/CTRL+D should be enough for it to print 'OK\n'."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker 1 2 3 4 5
	# \n => Error
	
	echo "Test:"
	echo "Passing a newline, then EOF, to a sorted argument list."
	echo -e "${LGRN}echo \"\" | ./checker 1 2 3 4 5${NC}"
	echo "" | ./checker 1 2 3 4 5 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "A newline isn't a valid operation"
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	# ./checker 2 1 3 4 5
	# sa\n
	# pb\n
	# pb\n
	# pa\n
	# pa\n
	# EOF
	# => OK
	
	echo "Test:"
	echo "Passing valid operations to an unsorted list."
	echo -e "${LGRN}echo -e \"sa\npb\npb\npa\npa\" | ./checker 2 1 3 4 5${NC}"
	echo -e "sa\npb\npb\npa\npa" | ./checker 2 1 3 4 5 1>/tmp/Output 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) == 'Error$' ]] || [[ $(cat -e /tmp/Output) == 'KO$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is not an error, nor is it a KO."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker 2 1 3 4 5
	# sa\n
	# pb\n
	# pb\n
	# pa\n
	# EOF
	# => Error
	
	echo "Test:"
	echo "Passing insufficient operations to an unsorted list."
	echo -e "${LGRN}echo -e \"sa\npb\npb\npa\" | ./checker 2 1 3 4 5${NC}"
	echo -e "sa\npb\npb\npa" | ./checker 2 1 3 4 5 1>/tmp/Output 2>/dev/null
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Output) != 'KO$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "This is an error, Stack A has been so far sorted,"
		echo "but not all stack elements have been pushed to it,"
		echo "one 'pa' operation is still missing. 'KO\n' should be printed on stdout."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker 2 1
	# sa\n
	# EOF
	# should print OK
	
	echo "Test:"
	echo "Passing a valid swap operation to an argument list of size 2."
	echo -e "${LGRN}echo -e \"sa\" | ./checker 2 1${NC}"
	echo -e "sa" | ./checker 2 1 1>/tmp/Output 2>/dev/null
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Output) != 'OK$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Swapping 2 1 should return 'OK\n' on stdout."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker 2 1
	# s\n
	# should print Error
	
	echo "Test:"
	echo "Passing an invalid operation to an argument list of size 2."
	echo -e "${LGRN}echo -e \"s\" | ./checker 2 1${NC}"
	echo -e "s" | ./checker 2 1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Whoops. 's\n' is not a valid operation."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	# ./checker 2 1
	# sas\n
	# should print Error
	
	echo "Test:"
	echo "Passing an invalid operation to an argument list of size 2."
	echo -e "${LGRN}echo -e \"sas\" | ./checker 2 1${NC}"
	echo -e "sas" | ./checker 2 1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Whoops. 'sas\n' is not a valid operation."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	# ./checker 2 1
	# saCTRL+D
	# should print Error
	
	echo "Test:"
	echo "Typing a valid operation and then EOF/CTRL+D (instead of a newline)."
	echo -e "${LGRN}echo -n \"sa\" | ./checker 2 1${NC}"
	echo -n "sa" | ./checker 2 1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo -e "Whoops. 'sa${BLU}EOF${NC}' is not a valid operation."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	# ./checker 1
	# EOF => OK
	
	echo "Test:"
	echo "Passing EOF/CTRL+D to an argument list of size 1."
	echo -e "${LGRN}echo -n \"\" | ./checker 1${NC}"
	echo -n "" | ./checker 1 1>/tmp/Output 2>/dev/null
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Output) != 'OK$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "List is already sorted, so EOF/CTRL+D should be sufficient."
		echo "'OK\n' should be printed on stdout."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker 1
	# \n => Error
	
	echo "Test:"
	echo "Passing a newline to an argument list of size 1."
	echo -e "${LGRN}echo \"\" | ./checker 1${NC}"
	echo "" | ./checker 1 1>/dev/null 2>/tmp/Error
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Error) != 'Error$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "Newline isn't a valid operation."
		echo -e "You should return '${UNDRLN}Error${BLU}\\\n${NC}' on ${UNDRLN}stderr${NC}."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 255 ]]
	then
		echo -e "${RED}Exit code should be 255.${NC}"
	fi
	echo ""
	
	# ./checker 1
	# any ops except pb should work (except if after pb a pa was performed).
	# EOF
	# should print OK
	
	ops=(sa sb ss pa ra rb rr rra)
	for op in "${ops[@]}"
	do
		echo "Test:"
		echo "Passing $op to an argument list of size 1."
		echo -e "${LGRN}echo -e \"$op\" | ./checker 1${NC}"
		echo -e "$op" | ./checker 1 1>/tmp/Output 2>/dev/null
		tmpExitCode=$?
		if [[ $(cat -e /tmp/Output) != 'OK$' ]]
		then
			echo -e "${RED}NOT OK:${NC}"
			echo "Operating $op shouldn't affect this stack,"
			echo "'OK\n' should be returned on stdout."
		else
			echo -e "${GRN}OK.${NC}"
		fi
		if [[ $tmpExitCode != 0 ]]
		then
			echo -e "${RED}Exit code should be 0.${NC}"
		fi
		echo ""
	done
	
	# ./checker 1
	# pb
	# EOF
	# should print KO
	
	echo "Test:"
	echo "Passing pb to an argument list of size 1."
	echo -e "${LGRN}echo -e \"pb\" | ./checker 1${NC}"
	echo -e "pb" | ./checker 1 1>/tmp/Output 2>/dev/null
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Output) != 'KO$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "The one and only element of stack A was pushed to stack B,"
		echo "Stack A is now empty and 'KO\n' should be returned on stdout."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker 1
	# pb
	# pb
	# EOF
	# should print KO
	
	echo "Test:"
	echo "Passing two pb operations to an argument list of size 1."
	echo -e "${LGRN}echo -e \"pb\npb\" | ./checker 1${NC}"
	echo -e "pb\npb" | ./checker 1 1>/tmp/Output 2>/dev/null
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Output) != 'KO$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "The one and only element of stack A was pushed to stack B,"
		echo "Stack A is now empty and 'KO\n' should be returned on stdout."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker 1
	# pb
	# pb
	# pa
	# EOF
	# should print OK
	
	echo "Test:"
	echo "Passing two pb operations and then pa to an argument list of size 1."
	echo -e "${LGRN}echo -e \"pb\npb\npa\" | ./checker 1${NC}"
	echo -e "pb\npb\npa" | ./checker 1 1>/tmp/Output 2>/dev/null
	tmpExitCode=$?
	if [[ $(cat -e /tmp/Output) != 'OK$' ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "The one and only element of stack A is first pushed to B,"
		echo "and lastly pushed back to A. 'OK\n' should be returned on stdout."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
	
	# ./checker
	# nothing should happen
	
	echo "Test:"
	echo "Not passing anything to an empty argument list."
	echo -e "${LGRN}./checker${NC}"
	./checker 1>/tmp/Output 2>/tmp/Error
	tmpExitCode=$?
	if [[ -s /tmp/Output ]] || [[ -s /tmp/Error ]]
	then
		echo -e "${RED}NOT OK:${NC}"
		echo "You should print nothing, neither on stdout,"
		echo "nor on stderr, nor take from stdin."
	else
		echo -e "${GRN}OK.${NC}"
	fi
	if [[ $tmpExitCode != 0 ]]
	then
		echo -e "${RED}Exit code should be 0.${NC}"
	fi
	echo ""
fi
