#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ALERT
// ASKFILE
// BREAK
// *  CALL
// CASE
// ** CLS
// CURSOR
// CURSCHAR
// CURSCOL
// CURSPOS
// DELETE
// DO
// ELSE
// END
// FILES
// FOR
// GETKEY
// GOSUB
// GOTO
// IF
// INCLUDE
// INK
// INPUT
// LEN
// LISTBOX
// LOAD
// MOVE
// NEXT
// NUMBER
// *  PAGE
// ** PAUSE
// PEEK
// POKE
// PORT
// ** PRINT
// RAND
// READ
// ** REM
// RENAME
// RETURN
// SAVE
// SERIAL
// SIZE
// SOUND
// STRING
// WAITKEY

char * programbuffer;
int programpointer = 0;
char* examplestr = "print \"Hello world\"";

void main(int argc,char** argv){
	printf("MikeBASIC Interpeter created by A. De Regt\n");
	printf("Created at 23 August 2018\n");
	printf("100%% compatible with MikeBASIC version 4.5\n");
	printf("See http://mikeos.sourceforge.net/handbook-appdev-basic.html for manual\n");
	printf("\n");
	printf("Program called at %s\n",argv[0]);
	if(argc>1){
		printf("Loading %s\n",argv[1]);
		FILE * bestand = fopen(argv[1],"rb");
		if(bestand){
			fseek(bestand,0,SEEK_END);
			long length = ftell(bestand);
			fseek(bestand,0,SEEK_SET);
			programbuffer = malloc(length);
			fread(programbuffer,1,length,bestand);
			printf("%li bytes loaded into memory!\n",length);
		}else{
			printf("Unable to load %s. Quiting.\n",argv[1]);
			exit(1);
		}
		fclose(bestand);
	}else{
		printf("Loading sample file\n");
		programbuffer = examplestr;
	}
	printf("\n\n");
	//
	// START PROGRAM
	//
	programpointer = 0;
	while(1){
		char eersteteken = programbuffer[programpointer++];
		if(eersteteken==0x00){
			printf("WARNING: Reached end of program\n");
			break;
		}else if(eersteteken==' '||eersteteken=='\n'||eersteteken=='\t'){
			continue;
		}
		//
		// Looking for keyword
		//
		int issetter = 1;// is setter unless method found
		if(eersteteken=='c'||eersteteken=='C'){
			char tweedeteken = programbuffer[programpointer++];
			if(tweedeteken=='a'||tweedeteken=='A'){
				char derdeteken = programbuffer[programpointer++];
				if(derdeteken=='l'||derdeteken=='L'){
					char vierdeteken = programbuffer[programpointer++];
					if(vierdeteken=='l'||vierdeteken=='L'){
						char vijfdeteken = programbuffer[programpointer++];
						if(vijfdeteken==' '){
							//
							// CALL detected
							// CALL [LABEL:LOCATION]
							//
							issetter = 0;
							char def = programbuffer[programpointer++];
							//check if its loc or lab
							if(def=='0'||def=='1'||def=='2'||def=='3'||def=='4'||def=='5'||def=='6'||def=='7'||def=='8'||def=='9'){
								printf("PANIC: CALL TO LOCATION NOT SUPPORTED!\n");
								exit(1);
							}else{
								char usrnme[10]; // buffer for lookupstr
							}
							// to newline
							while(1){
								char deze = programbuffer[programpointer++];
								if(deze=='\n'){
									break;
								}
							}
						}
					}
				}
			}else if(tweedeteken=='l'||tweedeteken=='L'){
				char derdeteken = programbuffer[programpointer++];
				if(derdeteken=='s'||derdeteken=='S'){
					char vierdeteken = programbuffer[programpointer++];
					if(vierdeteken==' '||vierdeteken=='\n'){
						//
						// CLS detected
						// CLS
						//
						issetter = 0;
						printf(">>> I SHOULD CLEAR NOW <<< \n");
						// end of line
						if(vierdeteken!='\n'){
							while(1){
								char deze = programbuffer[programpointer++];
								if(deze=='\n'){
									break;
								}
							}
						}
					}
				}
			}
		}else if(eersteteken=='r'||eersteteken=='R'){
			char tweedeteken = programbuffer[programpointer++];
			if(tweedeteken=='e'||tweedeteken=='E'){
				char derdeteken = programbuffer[programpointer++];
				if(derdeteken=='m'||derdeteken=='M'){
					char vierdeteken = programbuffer[programpointer++];
					if(vierdeteken==' '){
						//
						// REM detected
						// REM ...
						//
						issetter = 0;
						while(1){
							char deze = programbuffer[programpointer++];
							if(deze==0x00||deze=='\n'){
								break;
							}
						}
					}
				}
			}
		}else if(eersteteken=='p'||eersteteken=='P'){
			char tweedeteken = programbuffer[programpointer++];
			if(tweedeteken=='a'||tweedeteken=='A'){
				char derdetoken = programbuffer[programpointer++];
				if(derdetoken=='g'||derdetoken=='G'){
					char vierdetoken = programbuffer[programpointer++];
					if(vierdetoken=='e'||vierdetoken=='E'){
						char vijfdetoken = programbuffer[programpointer++];
						if(vijfdetoken==' '){
							//
							// PAGE detected.
							// PAGE [PAGEA] [PAGEB]
							//
							issetter = 0;
						}
					}
				}else if(derdetoken=='u'||derdetoken=='U'){
					char vierdetoken = programbuffer[programpointer++];
					if(vierdetoken=='s'||vierdetoken=='S'){
						char vijfdetoken = programbuffer[programpointer++];
						if(vijfdetoken=='e'||vijfdetoken=='E'){
							char zesdetoken = programbuffer[programpointer++];
							if(zesdetoken==' '){
								//
								// PAUSE detected.
								// PAUSE [INT]
								//
								issetter = 0;
								char deze = programbuffer[programpointer++];
								int ammount = 5;
								if(deze=='0'||deze=='1'||deze=='2'||deze=='3'||deze=='4'||deze=='5'||deze=='6'||deze=='7'||deze=='8'||deze=='9'){
									// is number
									char bfx[10];
									int y = 0;
									bfx[y++] = deze;
									while(1){
										char oink = programbuffer[programpointer+(y-1)];
										if(oink==' '||oink=='\n'||oink==0x00){
											break;
										}
										bfx[y++] = oink;
									}
									bfx[y++] = 0x00;
									ammount = atoi(bfx);
								}else{
									// is variabele
								}
								sleep(ammount);
								// move to end of line
								while(1){
									deze = programbuffer[programpointer++];
									if(deze=='\n'){
										break;
									}
								}
							}
						}
					}
				}
			}else if(tweedeteken=='r'||tweedeteken=='R'){
				char derdeteken = programbuffer[programpointer++];
				if(derdeteken=='i'||derdeteken=='I'){
					char vierdeteken = programbuffer[programpointer++];
					if(vierdeteken=='n'||vierdeteken=='N'){
						char vijfdeteken = programbuffer[programpointer++];
						if(vijfdeteken=='t'||vijfdeteken=='T'){
							char zesdeteken = programbuffer[programpointer++];
							if(zesdeteken==' '){
								//
								// PRINT detected.
								// PRINT [STRING|VARIABELE]
								//
								issetter = 0;
								char takdetect = programbuffer[programpointer++];
								if(takdetect=='\"'){
									//
									// Is STRING. Loop untill end of "
									//
									while(1){
										char deze = programbuffer[programpointer++];
										if(deze=='\"'){
											break;
										}
										printf("%c",deze);
									}
								}else{
									//
									// Is VARIABELE. Lookup arg and print
									//
									if(takdetect=='$'){
										// is String variabele
									}else{
										// is numeric variabele
									}
								}
								//
								// Loop untill end of line if ; detected then no new line
								//
								int needsnewline = 1;
								while(1){
									char deze = programbuffer[programpointer++];
									if(deze==0x00||deze=='\n'){
										break;
									}
									if(deze==';'){
										needsnewline = 0;
									}
								}
								if(needsnewline){
									printf("\n");
								}
							}
						}
					}
				}
			}
		}
		if(issetter){
			//
			// Can be two things: a statement: A = B or a label: A:
			//
			int type = 0;
			int hidden = 0;
			while(1){
				char deze = programbuffer[programpointer+(hidden++)];
				if(deze==':'){
					type = 1;
					break;
				}else if(deze==0x00||deze=='\n'){
					break;
				}else if(deze=='='){
					type = 2;
					break;
				}
			}
			if(type==0){
				//printf("Syntaxis error\n");
			}else if(type==1){
				//printf("Label detected!\n");
			}else if(type==2){
				//printf("Statement detected!\n");
			}
		}
	}
}
