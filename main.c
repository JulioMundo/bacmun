#include<18F4550.H>
#fuses HSPLL, PLL5, USBDIV, NOWDT, CPUDIV1, NOPROTECT, NODEBUG, NOPBADEN, NOLVP, NOVREGEN, NOPUT, NOBROWNOUT//2OMHZ
#use delay(clock=48MHz)
#use fast_io(A)
#use I2C(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#define LCD_ENABLE_PIN  PIN_C0                                 
#define LCD_RS_PIN      PIN_C1                                 
#define LCD_RW_PIN      PIN_C2                                
#define LCD_DATA4       PIN_B4                                    
#define LCD_DATA5       PIN_B5                                  
#define LCD_DATA6       PIN_B6                                   
#define LCD_DATA7       PIN_B7
#include <lcd.c>
#include<lcd.c>
#include"KBD4x4.c"
#include<DS1307.c>
#include <stddef.h>
#define sgyear 31556936  
#define sgmes 2629743
#define sgdia 86400
#define sghora 3600
#define sgmn 60
#define constmk 31457299
#define resto 67328
#define marcatiempodefc11 (marcatiempodefc1)
int dia=19, mes=04, an=23, dow=5;
int hora=13,min=30,seg=0;
long a=0;
long b=0;
#include <string.h>
int concat(int num){
    static int aux = 0;
    if(num!=-1){
    aux =(aux * 10) + num  ;
    }else{
    aux=0;}
    return aux;
}
int getValue(){
    char tecla;
    char numbers[2];
    int count = 0, num; 
    
    do{
        tecla=kbd_getc();
        
        if(tecla!=0) {
if(tecla!='B'){
 numbers[count] = tecla;;
            lcd_putc(tecla);
            delay_ms(50);
            count++;
            
                if (count == 2 && tecla!='B') {

                for (int x = 0; x < sizeof(numbers); x++) {
                    num = concat(numbers[x] - 48);
                }
                   lcd_putc("\f");
                lcd_gotoxy(1, 1);
               lcd_putc("A=ok B=back");
                lcd_gotoxy(1, 2);
                printf(lcd_putc, "numero:%02u", num);
                delay_ms(50);
            }
}else {
num=0;
count=0;
lcd_putc("\f");
concat(-1);
}

        }
        
    }  while (tecla != 'A');
    
    
    return  num;
}
void main(void)
{
set_tris_a(0x00);
output_a(0x00);
int c1diainicial,c1mesinicial,c1anoinicial,c1horainicial,c1minutoinicial,c1segundoinicial,diaprogramadoc1,mesprogramadoc1,yearprogramadoc1,horaprogramadac1,minprogramadoc1, segprogramadoc1;
int c1diafinal,c1mesfinal,c1anofinal,c1horafinal,c1minutofinal,c1segundofinal,respuesta;
ds1307_set_date_time(dia,mes,an,dow,hora,min,seg);
char tecla;
char contra[2]; //aqui se guardan las teclas del teclado
int direccion=0;
lcd_init();
kbd_init();
//a partir de aqui es el inicio 

//aqui acaba
lcd_gotoxy(1,1);
lcd_putc("1=celda 2=temp       ");
lcd_gotoxy(1,2);
while(true){
ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
ds1307_get_time(hora, min, seg);//obtiene hora actual
if(dia==diaprogramadoc1&&mes==mesprogramadoc1&&an==yearprogramadoc1&&hora==horaprogramadac1&&min==minprogramadoc1&&seg==segprogramadoc1){
output_high(PIN_A0);
 lcd_putc("\f");
 lcd_gotoxy(1,1);
  printf(lcd_putc,"fecha:%02u/%02u/20%02u",diaprogramadoc1,mesprogramadoc1,yearprogramadoc1);
lcd_gotoxy(1,2);
printf(lcd_putc,"hora: %02u:%02u:%02u",horaprogramadac1,minprogramadoc1,segprogramadoc1);
delay_ms(10000);
output_low(PIN_A0);
lcd_putc("\f");
lcd_gotoxy(1,1);
lcd_putc("1=celda 2=temp       ");
lcd_gotoxy(1,2);
}
switch(getValue())
{
case 1:
                  lcd_putc("\f");
                  lcd_gotoxy(1,1);
                  printf(lcd_putc,"celda a editar?     ");
                  lcd_gotoxy(1,2);
                  direccion=0;
                  while(true){
                  tecla=kbd_getc();
                  if(tecla!=0){
                  contra[direccion]=tecla;;
                  lcd_putc(tecla);
                  delay_ms(50);
                  direccion=direccion+1; 
                  if(direccion==2){
                  switch(contra[0]=='0'&& contra[1]=='1'){
                  case 01:
                  lcd_putc("\f");
                  lcd_gotoxy(1,1);
                  lcd_putc("editaras C1...     ");
                  delay_ms(1500);
                                                        lcd_putc("\f");
                                                        lcd_gotoxy(1,1);
                                                        printf(lcd_putc,"1=iniciarCR 2=verCR    ");
                                                        lcd_gotoxy(1,2);
                                                        direccion=0;
                                                        while(true){
                                                        tecla=kbd_getc();
                                                        if(tecla!=0){
                                                        contra[direccion]=tecla;;
                                                        lcd_putc(tecla);
                                                        delay_ms(50);
                                                        direccion=direccion+1; 
                                                        if(direccion==2){
                                                        if(contra[0]=='0'&& contra[1]=='1'){
                                                       respuesta=1; }
                                                        if(contra[0]=='0'&& contra[1]=='2'){
                                                       respuesta=2; }
                                                       if(contra[0]=='0'&& contra[1]=='3'){
                                                       respuesta=3; }
                                                        switch(respuesta){
                                                        case 01:
                                                        lcd_putc("\f");
                  lcd_gotoxy(1,1);
                  lcd_putc("puso inicio    ");
                  delay_ms(1500);
                        lcd_gotoxy(1,1);
                                                        lcd_putc("\f");
                                                        lcd_putc("iniciando cronometro       ");
                                                        delay_ms(1500);
                                                        ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
                                                        ds1307_get_time(hora, min, seg);//obtiene hora actual
                                                        c1diainicial=dia;
                                                        c1mesinicial=mes;
                                                        c1anoinicial=an;
                                                        c1horainicial=hora;
                                                        c1minutoinicial=min;
                                                        c1segundoinicial=seg;
                                                        lcd_putc("\f");
                                                        lcd_gotoxy(1,1);
                                                        printf(lcd_putc,"fecha:%02u/%02u/20%02u", dia, mes, an);
                                                        lcd_gotoxy(1,2);
                                                        printf(lcd_putc,"hora: %02u:%02u:%02u", hora, min, seg);
                                                        delay_ms(2000);
                                                        lcd_putc("\f");break;
                  case 02:
                   lcd_putc("\f");
                  lcd_gotoxy(1,1);
                  lcd_putc("puso ver     ");
                  delay_ms(1500);
                  lcd_putc("\f");
                 lcd_putc("Hora de inicio:      ");
                 delay_ms(1500);
                  lcd_putc("\f");
                lcd_gotoxy(1,1);
               printf(lcd_putc,"fecha:%02u/%02u/20%02u", c1diainicial, c1mesinicial, c1anoinicial);
                lcd_gotoxy(1,2);
                printf(lcd_putc,"hora: %02u:%02u:%02u", c1horainicial, c1minutoinicial,c1segundoinicial);
                 delay_ms(2000);
               lcd_putc("\f");
               lcd_putc("Hora de actual:      ");
                 delay_ms(1500);
                 ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
                 ds1307_get_time(hora, min, seg);//obtiene hora actual
                  lcd_putc("\f");
                lcd_gotoxy(1,1);
               printf(lcd_putc,"fecha:%02u/%02u/20%02u", dia, mes, an);
                lcd_gotoxy(1,2);
                printf(lcd_putc,"hora: %02u:%02u:%02u", hora, min,seg);
                 delay_ms(2000);
               lcd_putc("\f");
                  break;
                  case 03:
                  lcd_putc("\f");
                  lcd_gotoxy(1,1);
                  lcd_putc("puso programar     ");
                  delay_ms(1500);
                  lcd_putc("\f");
                  lcd_gotoxy(1,1);
                  lcd_putc("dia final:     ");
                  delay_ms(1500);
                  direccion=0;
                  lcd_gotoxy(1,2);
                  while(true){
                  tecla=kbd_getc();
                  if(tecla!=0){
                  contra[direccion]=tecla;;
                  lcd_putc(tecla);
                  delay_ms(50);
                  direccion=direccion+1; 
                  if(direccion==2){
                  //dia
                  if(contra[0]=='0'&& contra[1]=='1'){
                  respuesta=1;}
                  if(contra[0]=='0'&& contra[1]=='2'){
                  respuesta=2;}
                  if(contra[0]=='0'&& contra[1]=='3'){
                  respuesta=3;}
                  if(contra[0]=='0'&& contra[1]=='4'){
                  respuesta=4;}
                  if(contra[0]=='0'&& contra[1]=='5'){
                  respuesta=5;}
                  if(contra[0]=='0'&& contra[1]=='6'){
                  respuesta=6;}
                  if(contra[0]=='0'&& contra[1]=='7'){
                  respuesta=7;}
                  if(contra[0]=='0'&& contra[1]=='8'){
                  respuesta=8;}
                  if(contra[0]=='0'&& contra[1]=='9'){
                  respuesta=9;}
                  if(contra[0]=='1'&& contra[1]=='0'){
                  respuesta=10;}
                   if(contra[0]=='1'&& contra[1]=='1'){
                  respuesta=11;}
                  if(contra[0]=='1'&& contra[1]=='2'){
                  respuesta=12;}
                  if(contra[0]=='1'&& contra[1]=='3'){
                  respuesta=13;}
                  if(contra[0]=='1'&& contra[1]=='4'){
                  respuesta=14;}
                  if(contra[0]=='1'&& contra[1]=='5'){
                  respuesta=15;}
                  if(contra[0]=='1'&& contra[1]=='6'){
                 respuesta=16;}
                  if(contra[0]=='1'&& contra[1]=='7'){
                  respuesta=17;}
                  if(contra[0]=='1'&& contra[1]=='8'){
                 respuesta=18;}
                  if(contra[0]=='1'&& contra[1]=='9'){
                 respuesta=19;}
                  if(contra[0]=='2'&& contra[1]=='0'){
                 respuesta=20;}
                   if(contra[0]=='2'&& contra[1]=='1'){
                  respuesta=21;}
                  if(contra[0]=='2'&& contra[1]=='2'){
                  respuesta=22;}
                  if(contra[0]=='2'&& contra[1]=='3'){
                  respuesta=23;}
                  if(contra[0]=='2'&& contra[1]=='4'){
                 respuesta=24;}
                  if(contra[0]=='2'&& contra[1]=='5'){
                  respuesta=25;}
                  if(contra[0]=='2'&& contra[1]=='6'){
                  respuesta=26;}
                  if(contra[0]=='2'&& contra[1]=='7'){
                  respuesta=27;}
                  if(contra[0]=='2'&& contra[1]=='8'){
                  respuesta=28;}
                  if(contra[0]=='2'&& contra[1]=='9'){
                 respuesta=29;}
                  if(contra[0]=='3'&& contra[1]=='0'){
                  respuesta=30;}
                  if(contra[0]=='3'&& contra[1]=='1'){
                  respuesta=31;}
                  if(contra[0]=='3'&& contra[1]=='2'){
                respuesta=32;} 
                             lcd_putc("\f");
                   delay_ms(2000);
                  lcd_gotoxy(1,1);
                  lcd_putc("dia ingresado:     ");
                  lcd_gotoxy(1,2);
                 printf(lcd_putc,"%02u",respuesta);                
                 diaprogramadoc1=respuesta;
                  delay_ms(2000);
                   lcd_putc("\f");
                   //mes
                   lcd_gotoxy(1,1);
                  lcd_putc("mes final:     ");
                  delay_ms(1500);
                  direccion=0;
                  lcd_gotoxy(1,2);
                  while(true){
                  tecla=kbd_getc();
                  if(tecla!=0){
                  contra[direccion]=tecla;;
                  lcd_putc(tecla);
                  delay_ms(50);
                  direccion=direccion+1; 
                  if(direccion==2){
                  if(contra[0]=='0'&& contra[1]=='1'){
                  respuesta=1;}
                  if(contra[0]=='0'&& contra[1]=='2'){
                  respuesta=2;}
                  if(contra[0]=='0'&& contra[1]=='3'){
                  respuesta=3;}
                  if(contra[0]=='0'&& contra[1]=='4'){
                  respuesta=4;}
                  if(contra[0]=='0'&& contra[1]=='5'){
                  respuesta=5;}
                  if(contra[0]=='0'&& contra[1]=='6'){
                  respuesta=6;}
                  if(contra[0]=='0'&& contra[1]=='7'){
                  respuesta=7;}
                  if(contra[0]=='0'&& contra[1]=='8'){
                  respuesta=8;}
                  if(contra[0]=='0'&& contra[1]=='9'){
                  respuesta=9;}
                  if(contra[0]=='1'&& contra[1]=='0'){
                  respuesta=10;}
                   if(contra[0]=='1'&& contra[1]=='1'){
                  respuesta=11;}
                  if(contra[0]=='1'&& contra[1]=='2'){
                  respuesta=12;}
                  lcd_putc("\f");
                   delay_ms(2000);
                  lcd_gotoxy(1,1);
                  lcd_putc("mes ingresado:     ");
                  lcd_gotoxy(1,2);
                 printf(lcd_putc,"%02u",respuesta);                
                 mesprogramadoc1=respuesta;
                  delay_ms(2000);
                   lcd_putc("\f");
                   //anio
                   lcd_gotoxy(1,1);
                  lcd_putc("year final:     ");
                  delay_ms(1500);
                  direccion=0;
                  lcd_gotoxy(1,2);
                  while(true){
                  tecla=kbd_getc();
                  if(tecla!=0){
                  contra[direccion]=tecla;;
                  lcd_putc(tecla);
                  delay_ms(50);
                  direccion=direccion+1; 
                  if(direccion==2){
                  if(contra[0]=='0'&& contra[1]=='1'){
                  respuesta=1;}
                  if(contra[0]=='0'&& contra[1]=='2'){
                  respuesta=2;}
                  if(contra[0]=='0'&& contra[1]=='3'){
                  respuesta=3;}
                  if(contra[0]=='0'&& contra[1]=='4'){
                  respuesta=4;}
                  if(contra[0]=='0'&& contra[1]=='5'){
                  respuesta=5;}
                  if(contra[0]=='0'&& contra[1]=='6'){
                  respuesta=6;}
                  if(contra[0]=='0'&& contra[1]=='7'){
                  respuesta=7;}
                  if(contra[0]=='0'&& contra[1]=='8'){
                  respuesta=8;}
                  if(contra[0]=='0'&& contra[1]=='9'){
                  respuesta=9;}
                  if(contra[0]=='1'&& contra[1]=='0'){
                  respuesta=10;}
                   if(contra[0]=='1'&& contra[1]=='1'){
                  respuesta=11;}
                  if(contra[0]=='1'&& contra[1]=='2'){
                  respuesta=12;}
                  if(contra[0]=='1'&& contra[1]=='3'){
                  respuesta=13;}
                  if(contra[0]=='1'&& contra[1]=='4'){
                  respuesta=14;}
                  if(contra[0]=='1'&& contra[1]=='5'){
                  respuesta=15;}
                  if(contra[0]=='1'&& contra[1]=='6'){
                 respuesta=16;}
                  if(contra[0]=='1'&& contra[1]=='7'){
                  respuesta=17;}
                  if(contra[0]=='1'&& contra[1]=='8'){
                 respuesta=18;}
                  if(contra[0]=='1'&& contra[1]=='9'){
                 respuesta=19;}
                  if(contra[0]=='2'&& contra[1]=='0'){
                 respuesta=20;}
                   if(contra[0]=='2'&& contra[1]=='1'){
                  respuesta=21;}
                  if(contra[0]=='2'&& contra[1]=='2'){
                  respuesta=22;}
                  if(contra[0]=='2'&& contra[1]=='3'){
                  respuesta=23;}
                  if(contra[0]=='2'&& contra[1]=='4'){
                 respuesta=24;}
                  if(contra[0]=='2'&& contra[1]=='5'){
                  respuesta=25;}
                  if(contra[0]=='2'&& contra[1]=='6'){
                  respuesta=26;}
                  if(contra[0]=='2'&& contra[1]=='7'){
                  respuesta=27;}
                  if(contra[0]=='2'&& contra[1]=='8'){
                  respuesta=28;}
                  if(contra[0]=='2'&& contra[1]=='9'){
                 respuesta=29;}
                  if(contra[0]=='3'&& contra[1]=='0'){
                  respuesta=30;}
                  if(contra[0]=='3'&& contra[1]=='1'){
                  respuesta=31;}
                  if(contra[0]=='3'&& contra[1]=='2'){
                respuesta=32;} 
                  if(contra[0]=='3'&& contra[1]=='3'){
                  respuesta=33;}
                  if(contra[0]=='3'&& contra[1]=='4'){
                  respuesta=34;}
                  if(contra[0]=='3'&& contra[1]=='5'){
                  respuesta=35;}
                  if(contra[0]=='3'&& contra[1]=='6'){
                  respuesta=36;}
                  if(contra[0]=='3'&& contra[1]=='7'){
                  respuesta=37;}
                  if(contra[0]=='3'&& contra[1]=='8'){
                  respuesta=38;}
                  if(contra[0]=='3'&& contra[1]=='9'){
                  respuesta=39;}
                  if(contra[0]=='4'&& contra[1]=='0'){
                 respuesta=40;}
                   if(contra[0]=='4'&& contra[1]=='1'){
                  respuesta=41;}
                  if(contra[0]=='4'&& contra[1]=='2'){
                  respuesta=42;}
                  if(contra[0]=='4'&& contra[1]=='3'){
                  respuesta=43;}
                  if(contra[0]=='4'&& contra[1]=='4'){
                 respuesta=44;}
                  if(contra[0]=='4'&& contra[1]=='5'){
                  respuesta=45;}
                  if(contra[0]=='4'&& contra[1]=='6'){
                  respuesta=46;}
                  if(contra[0]=='4'&& contra[1]=='7'){
                 respuesta=47;}
                  if(contra[0]=='4'&& contra[1]=='8'){
                 respuesta=48;}
                  if(contra[0]=='4'&& contra[1]=='9'){
                 respuesta=49;}
                  if(contra[0]=='5'&& contra[1]=='0'){
                  respuesta=50;}
                   if(contra[0]=='5'&& contra[1]=='1'){
                  respuesta=51;}
                  if(contra[0]=='5'&& contra[1]=='2'){
                  respuesta=52;}
                  if(contra[0]=='5'&& contra[1]=='3'){
                  respuesta=53;}
                  if(contra[0]=='5'&& contra[1]=='4'){
                  respuesta=54;}
                  if(contra[0]=='5'&& contra[1]=='5'){
                  respuesta=55;}
                  if(contra[0]=='5'&& contra[1]=='6'){
                  respuesta=56;}
                  if(contra[0]=='5'&& contra[1]=='7'){
                  respuesta=57;}
                  if(contra[0]=='5'&& contra[1]=='8'){
                  respuesta=58;}
                  if(contra[0]=='5'&& contra[1]=='9'){
                  respuesta=59;}
                  if(contra[0]=='6'&& contra[1]=='0'){
                  respuesta=60;}
                  if(contra[0]=='6'&& contra[1]=='1'){
                  respuesta=61;}
                  if(contra[0]=='6'&& contra[1]=='2'){
                  respuesta=62;} 
                  if(contra[0]=='6'&& contra[1]=='3'){
                  respuesta=63;}
                  if(contra[0]=='6'&& contra[1]=='4'){
                  respuesta=64;}
                  if(contra[0]=='6'&& contra[1]=='5'){
                  respuesta=65;}
                  if(contra[0]=='6'&& contra[1]=='6'){
                  respuesta=66;}
                  if(contra[0]=='6'&& contra[1]=='7'){
                  respuesta=67;}
                  if(contra[0]=='6'&& contra[1]=='8'){
                  respuesta=68;}
                  if(contra[0]=='6'&& contra[1]=='9'){
                  respuesta=69;}
                  if(contra[0]=='7'&& contra[1]=='0'){
                  respuesta=70;}
                   if(contra[0]=='7'&& contra[1]=='1'){
                  respuesta=71;}
                  if(contra[0]=='7'&& contra[1]=='2'){
                  respuesta=72;}
                  if(contra[0]=='7'&& contra[1]=='3'){
                  respuesta=73;}
                  if(contra[0]=='7'&& contra[1]=='4'){
                  respuesta=74;}
                  if(contra[0]=='7'&& contra[1]=='5'){
                  respuesta=75;}
                  if(contra[0]=='7'&& contra[1]=='6'){
                  respuesta=76;}
                  if(contra[0]=='7'&& contra[1]=='7'){
                  respuesta=77;}
                  if(contra[0]=='7'&& contra[1]=='8'){
                  respuesta=78;}
                  if(contra[0]=='7'&& contra[1]=='9'){
                  respuesta=79;}
                  if(contra[0]=='8'&& contra[1]=='0'){
                  respuesta=80;}
                   if(contra[0]=='8'&& contra[1]=='1'){
                  respuesta=81;}
                  if(contra[0]=='8'&& contra[1]=='2'){
                  respuesta=82;}
                  if(contra[0]=='8'&& contra[1]=='3'){
                  respuesta=83;}
                  if(contra[0]=='8'&& contra[1]=='4'){
                  respuesta=84;}
                  if(contra[0]=='8'&& contra[1]=='5'){
                  respuesta=85;}
                  if(contra[0]=='8'&& contra[1]=='6'){
                  respuesta=86;}
                  if(contra[0]=='8'&& contra[1]=='7'){
                  respuesta=87;}
                  if(contra[0]=='8'&& contra[1]=='8'){
                  respuesta=88;}
                  if(contra[0]=='8'&& contra[1]=='9'){
                  respuesta=89;}
                  if(contra[0]=='9'&& contra[1]=='0'){
                  respuesta=90;}
                  if(contra[0]=='9'&& contra[1]=='1'){
                  respuesta=91;}
                  if(contra[0]=='9'&& contra[1]=='2'){
                  respuesta=92;}                  
                  if(contra[0]=='9'&& contra[1]=='3'){
                  respuesta=93;}
                  if(contra[0]=='9'&& contra[1]=='4'){
                  respuesta=94;}
                  if(contra[0]=='9'&& contra[1]=='5'){
                  respuesta=95;}
                  if(contra[0]=='9'&& contra[1]=='6'){
                  respuesta=96;}
                  if(contra[0]=='9'&& contra[1]=='7'){
                  respuesta=97;}
                  if(contra[0]=='9'&& contra[1]=='8'){
                  respuesta=98;}
                  if(contra[0]=='9'&& contra[1]=='9'){
                  respuesta=99;}
                  lcd_putc("\f");
                   delay_ms(2000);
                  lcd_gotoxy(1,1);
                  lcd_putc("year ingresado:     ");
                  lcd_gotoxy(1,2);
                 printf(lcd_putc,"%02u",respuesta);                
                 yearprogramadoc1=respuesta;
                  delay_ms(2000);
                   lcd_putc("\f");
                   //hora
                   lcd_gotoxy(1,1);
                  lcd_putc("hora final:     ");
                  delay_ms(1500);
                  direccion=0;
                  lcd_gotoxy(1,2);
                  while(true){
                  tecla=kbd_getc();
                  if(tecla!=0){
                  contra[direccion]=tecla;;
                  lcd_putc(tecla);
                  delay_ms(50);
                  direccion=direccion+1; 
                  if(direccion==2){
                   if(contra[0]=='0'&& contra[1]=='1'){
                  respuesta=1;}
                  if(contra[0]=='0'&& contra[1]=='2'){
                  respuesta=2;}
                  if(contra[0]=='0'&& contra[1]=='3'){
                  respuesta=3;}
                  if(contra[0]=='0'&& contra[1]=='4'){
                  respuesta=4;}
                  if(contra[0]=='0'&& contra[1]=='5'){
                  respuesta=5;}
                  if(contra[0]=='0'&& contra[1]=='6'){
                  respuesta=6;}
                  if(contra[0]=='0'&& contra[1]=='7'){
                  respuesta=7;}
                  if(contra[0]=='0'&& contra[1]=='8'){
                  respuesta=8;}
                  if(contra[0]=='0'&& contra[1]=='9'){
                  respuesta=9;}
                  if(contra[0]=='1'&& contra[1]=='0'){
                  respuesta=10;}
                   if(contra[0]=='1'&& contra[1]=='1'){
                  respuesta=11;}
                  if(contra[0]=='1'&& contra[1]=='2'){
                  respuesta=12;}
                  if(contra[0]=='1'&& contra[1]=='3'){
                  respuesta=13;}
                  if(contra[0]=='1'&& contra[1]=='4'){
                  respuesta=14;}
                  if(contra[0]=='1'&& contra[1]=='5'){
                  respuesta=15;}
                  if(contra[0]=='1'&& contra[1]=='6'){
                 respuesta=16;}
                  if(contra[0]=='1'&& contra[1]=='7'){
                  respuesta=17;}
                  if(contra[0]=='1'&& contra[1]=='8'){
                 respuesta=18;}
                  if(contra[0]=='1'&& contra[1]=='9'){
                 respuesta=19;}
                  if(contra[0]=='2'&& contra[1]=='0'){
                 respuesta=20;}
                   if(contra[0]=='2'&& contra[1]=='1'){
                  respuesta=21;}
                  if(contra[0]=='2'&& contra[1]=='2'){
                  respuesta=22;}
                  if(contra[0]=='2'&& contra[1]=='3'){
                  respuesta=23;}
                  if(contra[0]=='2'&& contra[1]=='4'){
                 respuesta=24;}
                  lcd_putc("\f");
                   delay_ms(2000);
                  lcd_gotoxy(1,1);
                  lcd_putc("hora ingresada:     ");
                  lcd_gotoxy(1,2);
                 printf(lcd_putc,"%02u",respuesta);                
                 horaprogramadac1=respuesta;
                  delay_ms(2000);
                   lcd_putc("\f");
                   //min
                    lcd_gotoxy(1,1);
                  lcd_putc("min final:     ");
                  delay_ms(1500);
                  direccion=0;
                  lcd_gotoxy(1,2);
                  while(true){
                  tecla=kbd_getc();
                  if(tecla!=0){
                  contra[direccion]=tecla;;
                  lcd_putc(tecla);
                  delay_ms(50);
                  direccion=direccion+1; 
                  if(direccion==2){
                 if(contra[0]=='0'&& contra[1]=='1'){
                  respuesta=1;}
                  if(contra[0]=='0'&& contra[1]=='2'){
                  respuesta=2;}
                  if(contra[0]=='0'&& contra[1]=='3'){
                  respuesta=3;}
                  if(contra[0]=='0'&& contra[1]=='4'){
                  respuesta=4;}
                  if(contra[0]=='0'&& contra[1]=='5'){
                  respuesta=5;}
                  if(contra[0]=='0'&& contra[1]=='6'){
                  respuesta=6;}
                  if(contra[0]=='0'&& contra[1]=='7'){
                  respuesta=7;}
                  if(contra[0]=='0'&& contra[1]=='8'){
                  respuesta=8;}
                  if(contra[0]=='0'&& contra[1]=='9'){
                  respuesta=9;}
                  if(contra[0]=='1'&& contra[1]=='0'){
                  respuesta=10;}
                   if(contra[0]=='1'&& contra[1]=='1'){
                  respuesta=11;}
                  if(contra[0]=='1'&& contra[1]=='2'){
                  respuesta=12;}
                  if(contra[0]=='1'&& contra[1]=='3'){
                  respuesta=13;}
                  if(contra[0]=='1'&& contra[1]=='4'){
                  respuesta=14;}
                  if(contra[0]=='1'&& contra[1]=='5'){
                  respuesta=15;}
                  if(contra[0]=='1'&& contra[1]=='6'){
                 respuesta=16;}
                  if(contra[0]=='1'&& contra[1]=='7'){
                  respuesta=17;}
                  if(contra[0]=='1'&& contra[1]=='8'){
                 respuesta=18;}
                  if(contra[0]=='1'&& contra[1]=='9'){
                 respuesta=19;}
                  if(contra[0]=='2'&& contra[1]=='0'){
                 respuesta=20;}
                   if(contra[0]=='2'&& contra[1]=='1'){
                  respuesta=21;}
                  if(contra[0]=='2'&& contra[1]=='2'){
                  respuesta=22;}
                  if(contra[0]=='2'&& contra[1]=='3'){
                  respuesta=23;}
                  if(contra[0]=='2'&& contra[1]=='4'){
                 respuesta=24;}
                  if(contra[0]=='2'&& contra[1]=='5'){
                  respuesta=25;}
                  if(contra[0]=='2'&& contra[1]=='6'){
                  respuesta=26;}
                  if(contra[0]=='2'&& contra[1]=='7'){
                  respuesta=27;}
                  if(contra[0]=='2'&& contra[1]=='8'){
                  respuesta=28;}
                  if(contra[0]=='2'&& contra[1]=='9'){
                 respuesta=29;}
                  if(contra[0]=='3'&& contra[1]=='0'){
                  respuesta=30;}
                  if(contra[0]=='3'&& contra[1]=='1'){
                  respuesta=31;}
                  if(contra[0]=='3'&& contra[1]=='2'){
                respuesta=32;} 
                  if(contra[0]=='3'&& contra[1]=='3'){
                  respuesta=33;}
                  if(contra[0]=='3'&& contra[1]=='4'){
                  respuesta=34;}
                  if(contra[0]=='3'&& contra[1]=='5'){
                  respuesta=35;}
                  if(contra[0]=='3'&& contra[1]=='6'){
                  respuesta=36;}
                  if(contra[0]=='3'&& contra[1]=='7'){
                  respuesta=37;}
                  if(contra[0]=='3'&& contra[1]=='8'){
                  respuesta=38;}
                  if(contra[0]=='3'&& contra[1]=='9'){
                  respuesta=39;}
                  if(contra[0]=='4'&& contra[1]=='0'){
                 respuesta=40;}
                   if(contra[0]=='4'&& contra[1]=='1'){
                  respuesta=41;}
                  if(contra[0]=='4'&& contra[1]=='2'){
                  respuesta=42;}
                  if(contra[0]=='4'&& contra[1]=='3'){
                  respuesta=43;}
                  if(contra[0]=='4'&& contra[1]=='4'){
                 respuesta=44;}
                  if(contra[0]=='4'&& contra[1]=='5'){
                  respuesta=45;}
                  if(contra[0]=='4'&& contra[1]=='6'){
                  respuesta=46;}
                  if(contra[0]=='4'&& contra[1]=='7'){
                 respuesta=47;}
                  if(contra[0]=='4'&& contra[1]=='8'){
                 respuesta=48;}
                  if(contra[0]=='4'&& contra[1]=='9'){
                 respuesta=49;}
                  if(contra[0]=='5'&& contra[1]=='0'){
                  respuesta=50;}
                   if(contra[0]=='5'&& contra[1]=='1'){
                  respuesta=51;}
                  if(contra[0]=='5'&& contra[1]=='2'){
                  respuesta=52;}
                  if(contra[0]=='5'&& contra[1]=='3'){
                  respuesta=53;}
                  if(contra[0]=='5'&& contra[1]=='4'){
                  respuesta=54;}
                  if(contra[0]=='5'&& contra[1]=='5'){
                  respuesta=55;}
                  if(contra[0]=='5'&& contra[1]=='6'){
                  respuesta=56;}
                  if(contra[0]=='5'&& contra[1]=='7'){
                  respuesta=57;}
                  if(contra[0]=='5'&& contra[1]=='8'){
                  respuesta=58;}
                  if(contra[0]=='5'&& contra[1]=='9'){
                  respuesta=59;}
                  if(contra[0]=='6'&& contra[1]=='0'){
                  respuesta=60;}
                  lcd_putc("\f");
                   delay_ms(2000);
                  lcd_gotoxy(1,1);
                  lcd_putc("min ingresado:     ");
                  lcd_gotoxy(1,2);
                 printf(lcd_putc,"%02u",respuesta);                
                 minprogramadoc1=respuesta;
                  delay_ms(2000);
                   lcd_putc("\f");
                   //seg
                           lcd_gotoxy(1,1);
                  lcd_putc("seg final:     ");
                  delay_ms(1500);
                  direccion=0;
                  lcd_gotoxy(1,2);
                  while(true){
                  tecla=kbd_getc();
                  if(tecla!=0){
                  contra[direccion]=tecla;;
                  lcd_putc(tecla);
                  delay_ms(50);
                  direccion=direccion+1; 
                  if(direccion==2){
                 if(contra[0]=='0'&& contra[1]=='1'){
                  respuesta=1;}
                  if(contra[0]=='0'&& contra[1]=='2'){
                  respuesta=2;}
                  if(contra[0]=='0'&& contra[1]=='3'){
                  respuesta=3;}
                  if(contra[0]=='0'&& contra[1]=='4'){
                  respuesta=4;}
                  if(contra[0]=='0'&& contra[1]=='5'){
                  respuesta=5;}
                  if(contra[0]=='0'&& contra[1]=='6'){
                  respuesta=6;}
                  if(contra[0]=='0'&& contra[1]=='7'){
                  respuesta=7;}
                  if(contra[0]=='0'&& contra[1]=='8'){
                  respuesta=8;}
                  if(contra[0]=='0'&& contra[1]=='9'){
                  respuesta=9;}
                  if(contra[0]=='1'&& contra[1]=='0'){
                  respuesta=10;}
                   if(contra[0]=='1'&& contra[1]=='1'){
                  respuesta=11;}
                  if(contra[0]=='1'&& contra[1]=='2'){
                  respuesta=12;}
                  if(contra[0]=='1'&& contra[1]=='3'){
                  respuesta=13;}
                  if(contra[0]=='1'&& contra[1]=='4'){
                  respuesta=14;}
                  if(contra[0]=='1'&& contra[1]=='5'){
                  respuesta=15;}
                  if(contra[0]=='1'&& contra[1]=='6'){
                 respuesta=16;}
                  if(contra[0]=='1'&& contra[1]=='7'){
                  respuesta=17;}
                  if(contra[0]=='1'&& contra[1]=='8'){
                 respuesta=18;}
                  if(contra[0]=='1'&& contra[1]=='9'){
                 respuesta=19;}
                  if(contra[0]=='2'&& contra[1]=='0'){
                 respuesta=20;}
                   if(contra[0]=='2'&& contra[1]=='1'){
                  respuesta=21;}
                  if(contra[0]=='2'&& contra[1]=='2'){
                  respuesta=22;}
                  if(contra[0]=='2'&& contra[1]=='3'){
                  respuesta=23;}
                  if(contra[0]=='2'&& contra[1]=='4'){
                 respuesta=24;}
                  if(contra[0]=='2'&& contra[1]=='5'){
                  respuesta=25;}
                  if(contra[0]=='2'&& contra[1]=='6'){
                  respuesta=26;}
                  if(contra[0]=='2'&& contra[1]=='7'){
                  respuesta=27;}
                  if(contra[0]=='2'&& contra[1]=='8'){
                  respuesta=28;}
                  if(contra[0]=='2'&& contra[1]=='9'){
                 respuesta=29;}
                  if(contra[0]=='3'&& contra[1]=='0'){
                  respuesta=30;}
                  if(contra[0]=='3'&& contra[1]=='1'){
                  respuesta=31;}
                  if(contra[0]=='3'&& contra[1]=='2'){
                respuesta=32;} 
                  if(contra[0]=='3'&& contra[1]=='3'){
                  respuesta=33;}
                  if(contra[0]=='3'&& contra[1]=='4'){
                  respuesta=34;}
                  if(contra[0]=='3'&& contra[1]=='5'){
                  respuesta=35;}
                  if(contra[0]=='3'&& contra[1]=='6'){
                  respuesta=36;}
                  if(contra[0]=='3'&& contra[1]=='7'){
                  respuesta=37;}
                  if(contra[0]=='3'&& contra[1]=='8'){
                  respuesta=38;}
                  if(contra[0]=='3'&& contra[1]=='9'){
                  respuesta=39;}
                  if(contra[0]=='4'&& contra[1]=='0'){
                 respuesta=40;}
                   if(contra[0]=='4'&& contra[1]=='1'){
                  respuesta=41;}
                  if(contra[0]=='4'&& contra[1]=='2'){
                  respuesta=42;}
                  if(contra[0]=='4'&& contra[1]=='3'){
                  respuesta=43;}
                  if(contra[0]=='4'&& contra[1]=='4'){
                 respuesta=44;}
                  if(contra[0]=='4'&& contra[1]=='5'){
                  respuesta=45;}
                  if(contra[0]=='4'&& contra[1]=='6'){
                  respuesta=46;}
                  if(contra[0]=='4'&& contra[1]=='7'){
                 respuesta=47;}
                  if(contra[0]=='4'&& contra[1]=='8'){
                 respuesta=48;}
                  if(contra[0]=='4'&& contra[1]=='9'){
                 respuesta=49;}
                  if(contra[0]=='5'&& contra[1]=='0'){
                  respuesta=50;}
                   if(contra[0]=='5'&& contra[1]=='1'){
                  respuesta=51;}
                  if(contra[0]=='5'&& contra[1]=='2'){
                  respuesta=52;}
                  if(contra[0]=='5'&& contra[1]=='3'){
                  respuesta=53;}
                  if(contra[0]=='5'&& contra[1]=='4'){
                  respuesta=54;}
                  if(contra[0]=='5'&& contra[1]=='5'){
                  respuesta=55;}
                  if(contra[0]=='5'&& contra[1]=='6'){
                  respuesta=56;}
                  if(contra[0]=='5'&& contra[1]=='7'){
                  respuesta=57;}
                  if(contra[0]=='5'&& contra[1]=='8'){
                  respuesta=58;}
                  if(contra[0]=='5'&& contra[1]=='9'){
                  respuesta=59;}
                  if(contra[0]=='6'&& contra[1]=='0'){
                  respuesta=60;}
                  lcd_putc("\f");
                   delay_ms(2000);
                  lcd_gotoxy(1,1);
                  lcd_putc("seg ingresado:     ");
                  lcd_gotoxy(1,2);
                 printf(lcd_putc,"%02u",respuesta);                
                 segprogramadoc1=respuesta;
                  delay_ms(2000);
                   lcd_putc("\f");
                   break;
                  }
                  }
                  }
                   break;
                  }
                  }
                  }
                   break;
                  }
                  }
                  }
                   break;
                  }
                  }
                  }
                   break;
                  }
                  }
                  }
                   
break;
                  }//aquiuba el primer if de la direccion
                  }//if del tecla diferente de 0
                  }//if del whiletrue
                  break;
                                                        }
                                                        break;
                                                       
                                                       }//del if de la direccion
                                                      
                                                       //si pones aqui un break tampoco avanza a dar la hora de inicio
                                                       }//del if tecla diferente de 0
                                                       
                                                        //si pones aqui un break no avanza a dar la hora de inicio
                                                        }//Del while iniciar ver
                                                   break;
                                                    case 02:
                                                    lcd_putc("\f");
                                                    lcd_gotoxy(1,1);
                                                        printf(lcd_putc,"seleccionaste c2");
                                                        delay_ms(1500);
                                                        break;
                                                        
                                                       }break;//del switch selector de celda
                
                  }//Del if con la direccion
                 
                  }//del if abajo del getc
                  
                  }//del while renglon 51

lcd_putc("\f");
lcd_gotoxy(1,1);
lcd_putc("1=celda 2=temp       ");
lcd_gotoxy(1,2);
direccion=0;
break;
case 02:
lcd_putc("\f");
lcd_gotoxy(1,1);
printf(lcd_putc,"seleccionaste temp");break;
default:
lcd_putc("\f");
lcd_gotoxy(1,1);
printf(lcd_putc,"no existe");
concat(-1);break;

}//del switch
}//del if condicional del con switch
}//del if abajo del while
