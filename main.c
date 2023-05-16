#include<18F4550.H>

#fuses HSPLL, PLL5, USBDIV, NOWDT, CPUDIV1, NOPROTECT, NODEBUG, NOPBADEN, NOLVP, NOVREGEN, NOPUT, NOBROWNOUT//2OMHZ
#use delay(clock=8MHz, crystal)
#use standard_io(A)
#define DHT11_PIN PIN_A1
#use I2C(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#define LCD_ENABLE_PIN  PIN_C0
#define LCD_RS_PIN      PIN_C1
#define LCD_RW_PIN      PIN_C2
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7

#include <lcd.c>
#include<DHT11.c>
#include <stdio.h>
#include<KBD4x4.c>
#include<DS1307.c>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>//array

#define marcatiempodefc11 (marcatiempodefc1)
int data_ok = 0, dow = 5;
float humedad, temperatura;


/**
 *  Error message
 * */
void notExist() {
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    printf(lcd_putc, "Upss! incorrecto");
    delay_ms(1000);
    lcd_putc("\f");
}

/**
 *  join number int type
 * */
int concat(int num) {
    static int aux = 0;
    if (num != -1) {
        aux = (aux * 10) + num;
    } else {
        aux = 0;
    }
    return aux;
}

/**
 * Function to get numbers by Matrix keyboard
 * */
int getValue() {
    concat(-1);
    char tecla;
    char numbers[2];
    int count = 0, num;

    do {
        tecla = kbd_getc();

        if (tecla != 0) {
            if (tecla != 'B') {
                numbers[count] = tecla;;
                lcd_putc(tecla);
                delay_ms(50);
                count++;

                if (count == 2 && tecla != 'B') {

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
            } else {
                num = 0;
                count = 0;
                lcd_putc("\f");
                concat(-1);
            }

        }

    } while (tecla != 'A');


    return num;
}


void main(void) {

    /**
    * Start ports
    */
    set_tris_a(0x00);
    output_a(0x00);
    set_tris_a(0xFF);
    lcd_init();
    kbd_init();
    delay_ms(1500);


    /*
     *  Project Brand
     */
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    lcd_putc("\t\t---MAJU--- ");
    lcd_gotoxy(1, 2);
    lcd_putc("\t---INCUBADORA--- ");
    delay_ms(1000);

    /*
     * Ask date and time
     */
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    lcd_putc("Día:");
    delay_ms(1000);
    int dia = getValue();
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    lcd_putc("Mes:");
    delay_ms(1000);
    int mes = getValue();
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    printf(lcd_putc(), "A%co alarma:", 164);
    delay_ms(1000);
    int an = getValue();
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    lcd_putc("Hora:");
    delay_ms(1000);
    int hora = getValue();
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    lcd_putc("Minuto:");
    delay_ms(1000);
    int min = getValue();
    lcd_putc("\f");
    lcd_gotoxy(1, 1);
    lcd_putc("Segundo:");
    delay_ms(1000);
    int seg = getValue();
    lcd_putc("\f");


    ds1307_set_date_time(dia, mes, an, dow, hora, min, seg);

    float temperaturadeseada = -1;
    char tecla, contra[2]; //aqui se guardan las teclas del teclado
    int direccion = 0, opt = 0;


    /**
     *  Array to save data about place (time and day) and (alarms)
     */
    int array[15][6], alarms[15][6];


    /**
     * Begin software
     */
    while (true) {


        ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
        ds1307_get_time(hora, min, seg);//obtiene hora actual
        
        if (input(PIN_A3) != 1) {
            int a;
            delay_ms(1500);
            lcd_putc("\f");
            a = 1;
            a = DHT11_read_data(&humedad, &temperatura);
            lcd_gotoxy(1, 2);
            printf(lcd_putc, "T:%0.1fC", temperatura);
            a = 0;
            lcd_gotoxy(1, 1);
            lcd_putc("Presiona Boton       ");
            lcd_gotoxy(9, 2);
            printf(lcd_putc, "->%0.1fC", temperaturadeseada);
            delay_ms(50);

            if (temperaturadeseada != -1 || temperaturadeseada == temperatura) {

                if (temperaturadeseada > temperatura) {
                    output_low(PIN_A5);
                    output_high(PIN_A4);
                } else {
                    output_low(PIN_A4);
                    output_high(PIN_A5);
                }

            } else {
                output_low(PIN_A4);
                output_low(PIN_A5);
            }

            /**
             * Check Alarm 
             */

            for (int i = 0; i < 15; ++i) {
                if (dia == alarms[i][0] && mes == alarms[i][1] && an == alarms[i][2] &&
                    hora == alarms[i][3] && min == alarms[i][4] && seg == alarms[i][5]) {
                    output_high(PIN_A0);
                    lcd_putc("\f");
                    lcd_gotoxy(1, 1);
                    printf(lcd_putc, "fecha:%02u/%02u/20%02u", alarms[i][0], alarms[i][1], alarms[i][2]);
                    lcd_gotoxy(1, 2);
                    printf(lcd_putc, "hora: %02u:%02u:%02u", alarms[i][3], alarms[i][4], alarms[i][5]);
                    delay_ms(10000);
                    output_low(PIN_A0);
                }
            }

        } else { goto salto; }


        salto:
        lcd_putc("\f");
        lcd_gotoxy(1, 1);
        lcd_putc("1.-Celda 2.-Temp       ");
        lcd_gotoxy(1, 2);

        opt = getValue();

        if (opt == 1) {
            lcd_putc("\f");
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "Eligir Celda     ");
            lcd_gotoxy(1, 2);
            opt = getValue();

            if (opt > 0 && opt <= 15) {
                lcd_putc("\f");
                lcd_gotoxy(1, 1);
                printf(lcd_putc, "Celda C%d ", opt);
                delay_ms(1000);
                lcd_putc("\f");
                lcd_gotoxy(1, 1);
                printf(lcd_putc, "1.IniciarCR 2.VerCR 3.Alarma ");
                lcd_gotoxy(1, 2);

                switch (getValue()) {
                    case 1:
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("Iniciar Cronometro    ");
                        delay_ms(1000);
                        lcd_gotoxy(1, 1);
                        lcd_putc("\f");
                        lcd_putc("Iniciando..       ");
                        delay_ms(1000);
                        ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
                        ds1307_get_time(hora, min, seg);//obtiene hora actual

                        array[opt - 1][0] = dia;
                        array[opt - 1][1] = mes;
                        array[opt - 1][2] = an;
                        array[opt - 1][3] = hora;
                        array[opt - 1][4] = min;
                        array[opt - 1][5] = seg;

                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "fecha:%02u/%02u/20%02u", dia, mes, an);
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "hora: %02u:%02u:%02u", hora, min, seg);
                        delay_ms(1500);
                        lcd_putc("\f");
                        break;
                    case 2:
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("Ver cronometro     ");
                        delay_ms(1000);
                        lcd_putc("\f");
                        lcd_putc("Hora de inicio:      ");
                        delay_ms(1000);
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "Fecha:%02u/%02u/20%02u", array[opt - 1][0], array[opt - 1][1],
                               array[opt - 1][2]);
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "Hora: %02u:%02u:%02u", array[opt - 1][3], array[opt - 1][4],
                               array[opt - 1][5]);
                        delay_ms(1500);
                        lcd_putc("\f");
                        lcd_putc("Hora de actual:      ");
                        delay_ms(1000);
                        ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
                        ds1307_get_time(hora, min, seg);//obtiene hora actual
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "Fecha:%02u/%02u/20%02u", dia, mes, an);
                        lcd_gotoxy(1, 2);
                        printf(lcd_putc, "Hora: %02u:%02u:%02u", hora, min, seg);
                        delay_ms(1500);
                        lcd_putc("\f");
                        break;
                    case 3:
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("Programar Alarma     ");
                        delay_ms(1000);
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("Día alarma:");
                        delay_ms(1000);

                        alarms[opt - 1][0] = getValue();

                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("Mes alarma:");
                        delay_ms(1000);

                        alarms[opt - 1][1] = getValue();


                        lcd_putc("\f");
                        //anio
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc(), "A%co alarma:", 164)
                        delay_ms(1000);

                        alarms[opt - 1][2] = getValue();

                        lcd_putc("\f");
                        delay_ms(1500);
                        lcd_gotoxy(1, 1);
                        lcd_putc("Fecha Alarma:     ");
                        lcd_gotoxy(1, 2);

                        printf(lcd_putc, "Alarma:%02u/%02u/20%02u", alarms[opt - 1][0], alarms[opt - 1][1],
                               alarms[opt - 1][2]);

                        delay_ms(1500);
                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);

                        lcd_putc("Hora Alarma:     ");
                        delay_ms(1000);

                        alarms[opt - 1][3] = getValue();

                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("Minuto Alarma:     ");
                        delay_ms(1000);

                        alarms[opt - 1][4] = getValue();

                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        lcd_putc("Segundo Alarma:     ");
                        delay_ms(1000);

                        alarms[opt - 1][5] = getValue();

                        lcd_putc("\f");
                        lcd_gotoxy(1, 1);
                        printf(lcd_putc, "P.Fecha:%02u/%02u/20%02u", alarms[opt - 1][0], alarms[opt - 1][1],
                               alarms[opt - 1][2]);

                        lcd_gotoxy(1, 2);

                        printf(lcd_putc, "P.Hora: %02u:%02u:%02u", alarms[opt - 1][3], alarms[opt - 1][4],
                               alarms[opt - 1][5]);

                        delay_ms(2000);
                        break;

                    default:
                        notExist();
                }
            } else { notExist(); }

        } else if (opt == 2) {

            lcd_putc("\f");
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "Temperatura deseada:");
            lcd_gotoxy(1, 2);
            temperaturadeseada = getValue();
            lcd_putc("\f");
            lcd_gotoxy(1, 1);
            printf(lcd_putc, "Temperatura deseada:");
            lcd_gotoxy(1, 2);
            printf(lcd_putc, "%0.1fC", temperaturadeseada);
            delay_ms(1000);
            lcd_putc("\f");


        } else { notExist(); }


    }//del while true
}//del if abajo del while
