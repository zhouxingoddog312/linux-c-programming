#!/bin/bash
dialog --title "Questionnaire" --msgbox "Welcome to my simple survey" 9 18
dialog --title "Confirm" --yesno "Are you willing to take part?" 9 18
if [ $? -ne 0 ]
then
	dialog --infobox "thankyou anyway" 5 20
	sleep 2
	dialog --clear
	exit 0
fi
dialog --title "Questionnaire" --inputbox "Please enter your name" 9 30 2>_1.txt
Q_NAME=`cat _1.txt`
dialog --menu "$Q_NAME, what music do you like best?" 15 30 4 1 "classical" 2 "jazz" 3 "country" 4 "other" 2>_1.txt
Q_MUSIC=`cat _1.txt`
if [ "$Q_MUSIC" = "1" ]
then
	dialog --title "like classical" --msgbox "Good choice!" 12 25
else
	dialog --title "Doesn't like classical" --msgbox "shame" 12 25
fi
rm -f ./_1.txt
sleep 2
dialog --clear
exit 0
