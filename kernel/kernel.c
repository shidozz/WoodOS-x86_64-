#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "limine.h"
#include "includes/alloc.h"
//#include "includes/vga.h"
//#include "includes/keyboard.h"
//#include "includes/gdt.h"
//#include "includes/idt.h"
#include "includes/math.h"
#include "includes/apic.h"
#include "includes/com.h"
#include "includes/outb.h"
#include "includes/pic.h"
#include "includes/pit.h"
#include "includes/terminal.h"

static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

// Fonction principal du kernel.
void _start(void) {
    
    s_terminal_initialize();
    /* Appellation du terminal limine pour écrire:
    Shidozz
    tremble connard
    */
    
    // GDT INIT
    /*s_terminal_putstr("GDT initialisation\n");
    s_terminal_update();
    gdt_init();
    s_terminal_putstr("GDT initialiser\n");
    s_terminal_update();

    // IDT INIT
    s_terminal_putstr("IDT initialisation\n");
    s_terminal_update();
    idt_init();
    s_terminal_putstr("IDT initialiser\n");
    s_terminal_update();
    */
    // APIC INIT
    s_terminal_putstr("APIC initialisation\n");
    s_terminal_update();
    apic_init();
    s_terminal_putstr("APIC initialiser\n");
    s_terminal_update();
    // COM INIT
    s_terminal_putstr("COM initialisation\n");
    s_terminal_update();
    com_init();
    s_terminal_putstr("COM initialiser\n");
    s_terminal_update();

    // PIC INIT
    s_terminal_putstr("PIC initialisation\n");
    s_terminal_update();
    pic_init();
    s_terminal_putstr("PIC initialiser\n");
    s_terminal_update();

    // PIT INIT
    s_terminal_putstr("PIT initialisation\n");
        s_terminal_update();
    pit_init(50);
    s_terminal_putstr("PIT initialiser\n");
    s_terminal_update();

    // Fermeture du kernel
    s_terminal_putstr("Le kernel s'allume\n");
    s_terminal_update();
    bool isLaunch = true;

    // Boucle Infini pour le kernel
    while(isLaunch){
        s_terminal_update();
        //update_keyboard();
        /*Pixel blue;
        blue.red = 0;
        blue.green = 0;
        blue.blue = 255;
        
        drawCircle(320, 240, 100, blue);
        */
        /*if(is_key_down(27)){
            isLaunch = false;
        }*/

        //update_screen();
    }
    
    // Fermeture du kernel
    s_terminal_putstr("Le kernel est eteint\n");

    // La fin
    done();
}
