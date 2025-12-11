import sys
Zero = ["  ***  ", " *   * ", "*     *", "*     *", "*     *", " *   * ", "  ***  "]
One = ["   *   ", "  **   ", "   *   ", "   *   ", "   *   ", "   *   ", "  ***  "]
Two = [" ***   ", "*   *  ", "*  *   ", "   *   ", "  *    ", " *     ", "*****   "]
Three = ["  ***  ", " *   * ", "    *  ", "  ***  ", "    *  ", " *   * ", "  ***  "]
Four = ["*   *  ", "*   *  ", "*   *  ", "*****  ", "    *  ", "    *  ", "    *  "]
Five = ["*****  ", "*      ", "*      ", " ****  ", "    *  ", " *   * ", "  ***  "]
Six = ["  ***  ", " *     ", "*      ", " ****  ", "*   *  ", " *   * ", "  ***  "]
Seven = ["*****  ", "    *  ", "   *   ", "  *    ", " *     ", "*      ", "*      "]
Eight = ["  ***  ", " *   * ", "*     *", "  ***  ", "*     *", " *   * ", "  ***  "]
Nine = ["  ***  ", " *   * ", "*     *", "  ***  ", "    *  ", "    *  ", "    *  "]
Digits=[Zero,One,Two,Three,Four,Five,Six,Seven,Eight,Nine]
try:
    digits=sys.argv[1]
    row=0
    while row<7:
        line=""
        column=0
        while column<len(digits):
            number=int(digits[column])
            digit=Digits[number]
            current_row=digit[row]
            for ch in current_row:
                if ch=="*":
                    ch=str(number)
                line+=ch+" "
            column+=1
        print(line)
        row+=1
except IndexError:
    print("usage: bigdigits.py <number>")
except ValueError as err:
    print(err,"in",digits)
