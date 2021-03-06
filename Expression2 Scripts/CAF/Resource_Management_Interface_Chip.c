@name Resource Management Interface Chip
@inputs Energy:number Energy_Max:number X1A S1A S2A S3A S4A S5A S6A S7A H2O H2O_Max D2O D2O_Max
@outputs Screen_Text:string

Percentage = round(Energy / Energy_Max * 100)
Coolant_Percentage = round(H2O / H2O_Max * 100)
D2O_Percentage = round(D2O / D2O_Max * 100)
Screen_Text = " Energy Level - " + Percentage:toString() + "%"
Screen_Text = Screen_Text + "\n Coolant Level - " + Coolant_Percentage:toString() + "%"
Screen_Text = Screen_Text + "\n Deuterium Level - " + D2O_Percentage:toString() + "%"
Screen_Text = Screen_Text + "\n\n Fusion Reactor Cores -\n X1 Core - " + X1A + "   S1 Core - " + S1A + "\n S2 Core - " + S2A
Screen_Text = Screen_Text + "   S3 Core - " + S3A + "\n S4 Core - " + S4A + "   S5 Core - " + S5A + "\n S6 Core - " + S6A + "   S7 Core - " + S7A

#8 Reactors
#7 Secondary
