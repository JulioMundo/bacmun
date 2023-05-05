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
    concat(-1);
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
void main(void){

    set_tris_a(0x00);
    output_a(0x00);
    int c1diainicial,c1mesinicial,c1anoinicial,c1horainicial,c1minutoinicial,c1segundoinicial,diaprogramadoc1,mesprogramadoc1,yearprogramadoc1,horaprogramadac1,minprogramadoc1, segprogramadoc1;
    int c1diafinal,c1mesfinal,c1anofinal,c1horafinal,c1minutofinal,c1segundofinal,respuesta;
    ds1307_set_date_time(dia,mes,an,dow,hora,min,seg);
    char tecla;
    char contra[2]; //aqui se guardan las teclas del teclado
    int direccion=0, opt=0;
    lcd_init();
    kbd_init();
//a partir de aqui es el inicio

    while(true){

        lcd_gotoxy(1,1);
        lcd_putc("1=celda 2=temp       ");
        lcd_gotoxy(1,2);

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

        opt = getValue();

        if (opt==1){
            lcd_putc("\f");
            lcd_gotoxy(1,1);
            printf(lcd_putc,"celda a editar?     ");
            lcd_gotoxy(1,2);
            opt = getValue();

            if (opt>0 && opt<=15){
                lcd_putc("\f");
                lcd_gotoxy(1,1);
                lcd_putc("editaras C1...     ");
                delay_ms(1500);
                lcd_putc("\f");
                lcd_gotoxy(1,1);
                printf(lcd_putc,"1=iniciarCR 2=verCR  ");
                lcd_gotoxy(1,2);

                switch(getValue()) {
                    case 1:
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("puso inicio    ");
                        delay_ms(1500);
                        lcd_gotoxy(1, 1);
                        lcd_putc("\f");
                        lcd_putc("iniciando cronometro       ");
                        delay_ms(1500);
                        ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
                        ds1307_get_time(hora, min, seg);//obtiene hora actual
                        c1diainicial = dia;
                        c1mesinicial = mes;
                        c1anoinicial = an;
                        c1horainicial = hora;
                        c1minutoinicial = min;
                        c1segundoinicial = seg;
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "fecha:%02u/%02u/20%02u", dia, mes, an);
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "hora: %02u:%02u:%02u", hora, min, seg);
                        delay_ms(2000);
                        lcd_putc("\f");
                        break;
                    case 2:
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("puso ver     ");
                        delay_ms(1500);
                        lcd_putc("\f");
                        lcd_putc("Hora de inicio:      ");
                        delay_ms(1500);
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "fecha:%02u/%02u/20%02u", c1diainicial, c1mesinicial, c1anoinicial);
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "hora: %02u:%02u:%02u", c1horainicial, c1minutoinicial, c1segundoinicial);
                        delay_ms(2000);
                        lcd_putc("\f");
                        lcd_putc("Hora de actual:      ");
                        delay_ms(1500);
                        ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
                        ds1307_get_time(hora, min, seg);//obtiene hora actual
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "fecha:%02u/%02u/20%02u", dia, mes, an);
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "hora: %02u:%02u:%02u", hora, min, seg);
                        delay_ms(2000);
                        lcd_putc("\f");
                        break;
                    case 3:
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("puso programar     ");
                        delay_ms(1500);
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("dia final:     ");
                        delay_ms(1000);
                        diaprogramadoc1 = getValue();
                        lcd_putc("\f");
                        delay_ms(1000);
                        lcd_gotoxy(1, 1);
                        lcd_putc("dia ingresado:     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "%02u", diaprogramadoc1);
                        delay_ms(1000);
                        lcd_putc("\f");
                        //mes
                        lcd_gotoxy(1, 1);
                        lcd_putc("mes final:     ");
                        delay_ms(1000);
                        mesprogramadoc1 = getValue();
                        lcd_putc("\f");
                        delay_ms(2000);
                        lcd_gotoxy(1, 1);
                        lcd_putc("mes ingresado:     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "%02u", mesprogramadoc1);
                        delay_ms(1000);
                        lcd_putc("\f");
                        //anio
                        lcd_gotoxy(1, 1);
                        lcd_putc("year final:     ");
                        delay_ms(1500);
                        yearprogramadoc1 = getValue();
                        lcd_putc("\f");
                        delay_ms(2000);
                        lcd_gotoxy(1, 1);
                        lcd_putc("year ingresado:     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "%02u", yearprogramadoc1);
                        delay_ms(2000);
                        lcd_putc("\f");
                        //hora
                        lcd_gotoxy(1, 1);
                        lcd_putc("hora final:     ");
                        delay_ms(1000);
                        horaprogramadac1 = getValue();
                        lcd_putc("\f");
                        delay_ms(1000);
                        lcd_gotoxy(1, 1);
                        lcd_putc("hora ingresada:     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "%02u", horaprogramadac1);
                        delay_ms(1000);
                        lcd_putc("\f");
                        //min
                        lcd_gotoxy(1, 1);
                        lcd_putc("min final:     ");
                        delay_ms(1000);
                        minprogramadoc1 = getValue();
                        lcd_putc("\f");
                        delay_ms(1000);
                        lcd_gotoxy(1, 1);
                        lcd_putc("min ingresado:     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "%02u", minprogramadoc1);
                        delay_ms(1000);
                        lcd_putc("\f");
                        //seg
                        lcd_gotoxy(1, 1);
                        lcd_putc("seg final:     ");
                        delay_ms(1000);
                        segprogramadoc1 = getValue();
                        lcd_putc("\f");
                        delay_ms(1000);
                        lcd_gotoxy(1, 1);
                        lcd_putc("seg ingresado:     ");
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "%02u", segprogramadoc1);
                        delay_ms(1000);
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "fechp:%02u/%02u/20%02u", diaprogramadoc1, mesprogramadoc1, yearprogramadoc1);
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "horp: %02u:%02u:%02u", horaprogramadac1, minprogramadoc1, segprogramadoc1);
                        delay_ms(2000);
                        break;
                }
            }else{
                //no exitse este edificio
            }
        }else if(opt==2){
            lcd_putc("\f");
            lcd_gotoxy(1,1);
            printf(lcd_putc,"seleccionaste temp");
        }else{
            lcd_putc("\f");
            lcd_gotoxy(1,1);
            printf(lcd_putc,"no existe");
        }

    }//del while true
}//del if abajo del while
