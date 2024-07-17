extern malloc
extern fprintf
extern free
extern getCloneFunction
extern getPrintFunction
extern getDeleteFunction
extern intCmp
extern intClone
extern intDelete
extern intPrint
extern listNew
extern listPrint
extern listDelete
extern listClone
extern listAddFirst

global strClone
global strPrint
global strCmp
global strLen
global strDelete
global arrayNew
global arrayDelete
global arrayPrint
global arrayGetSize
global arrayAddLast
global arrayGet
global arrayRemove
global arraySwap
global cardCmp
global cardClone
global cardAddStacked
global cardDelete
global cardGetSuit
global cardGetNumber
global cardGetStacked
global cardPrint
global cardNew

section .data
corchete_abierto: db '[',0
coma_array: db ',',0
corchete_cerrado: db ']',0
null_str: db 'NULL',0
llaveAbierta_str: db '{',0
guion_str: db '-',0
llaveCerrada_str: db '}',0

section .text

%define OFFSET_TIPO 0
%define OFFSET_TAMANIO 4
%define OFFSET_CAPACIDAD 5
%define OFFSET_DATA 8
%define SIZE_STRUCT_ARRAY 16

%define TYPE_NONE 0
%define TYPE_INT 1
%define	TYPE_STRING 2
%define TYPE_CARD 3

%define SIZE_CARD 24
%define OFFSET_SUIT 0
%define OFFSET_NUMBER 8
%define OFFSET_STACKED 16

; ** String **
; char* strClone(char* a)
strClone:
    push rbp
    mov rbp, rsp
    xor rax, rax ; inicializo el contador en 0 -> inicilazas para no tener basura
    push r12 ; contador ciclo strlen 
    push r13 ; guardo la palabra
    push r14 ; nuevo contador para el ciclo
    sub rsp, 8
    xor r13, r13
	xor r14, r14 ; inicializo el contador en 0 -> inicilazas para no tener basura

    mov r13, rdi;
    call strLen

    .copia:
        mov r12, rax ; guardo el contador en r12 -> strlen
        inc r12 ; incremento el contador para que tenga el espacio para el nulo
        mov rdi, r12 ; guardo el contador en rdi para que sea el tamaño del nuevo string
        call malloc ; pido memoria para el nuevo string
        
    .cicloCopia:
        mov cl, [r13 + r14] ; guardo el caracter en ecx
        mov [rax + r14], cl ; guardo el caracter en el nuevo string
        inc r14 ; incremento el contador para que vaya recorriendo la palabra
        cmp r14, r12 ; comparo si el contador es igual al tamaño del nuevo string
        jne .cicloCopia ; si no es igual salta a cicloCopia

    .corte:
        add rsp, 8
        pop r14 ; recupero el contador
        pop r13 ; recupero la palabra
        pop r12 ; recupero el contador
        pop rbp ; recupero el puntero de pila
        ret

; void strPrint(char* a, FILE* pFile)
strPrint:
    push rbp
    mov rbp, rsp

    push r13 ;
    sub rsp, 8
    xor r13, r13 

    .condicion:
        mov r13, rdi ; guardo la palabra en r13
        cmp byte [r13], 0 ; camparas si el caracter es el nulo null == 0 
        je .imprimirNull ; si no es el nulo salta a copia

    .imprimir:
        mov rdi, rsi ; guardo el archivo en rdi
        mov rsi, r13 ; guardo la palabra en rsi
        call fprintf ; llamo a la función fprintf para imprimir la cadena en el archivo
        jmp .corte
    
    .imprimirNull:
        mov rdi, rsi ; guardo el archivo en rdi
        mov rsi, null_str ; guardo la palabra en rsi
        call fprintf ; llamo a la función fprintf para imprimir la cadena en el archivo

    .corte:
        add rsp, 8 ; libero el espacio de la pila
        pop r13 ; 
        pop rbp ; recupero el puntero de pila
        ret

; int32_t strCmp(char* a, char* b)
strCmp:
    push rbp ; alineado
    mov rbp, rsp
    push rbx ; para guardar la palabra a - desalineado
    push r12 ; para guardar la palabra b - alineado
    push r13 ; para guarda longitud de a - desalineado
    push r14 ; para guarda longitud de b - alineado
    push r10 ; para guardar la longitud minima - desalineado
    sub rsp, 8 ;- alineamos
    xor r15, r15 ; inicializo el contador en 0 -> inicilazas para no tener basura

    .guardarPalabras:
        mov rbx, rdi
        mov r12, rsi

    .inicializar_largos:
        mov rdi, rbx ; guardo rdi a rbx
        call strLen ; llamo strLen para calcular Len de a
        mov r13, rax ; guardo largo de a en r13
        mov rdi, r12 ; paso rsi en rdi
        call strLen
        mov r14, rax ; guardo largo de a en r13
        

    .obtenerLongitudMinima:
        cmp r13, r14 ; compara la longitud de a y b
        jb .set_minimo_a ; si longitud de a < longitud de b significa que a tiene menos caracteres
        cmp r13, r14
        ja .set_minimo_b ; ; si longitud de b < longitud de a significa que b tiene menos caracteres
        mov r10, r13 ; guardo cualquier longitud total son iguales
        ;jmp .condicion ; je .iguales - si longitudes son iguales no se salto!!
    
    .set_minimo_a:
        mov r10, r13
        jmp .condicion
    
    .set_minimo_b:
        mov r10, r14
        jmp .condicion

    .condicion:
        cmp r15, r10 ; compara contador con longitud_minima
        jne .comparar_caracter ; si i < longitud_minima, llamo comparar
        cmp r15, r10
        je .compararLen; si i >= longitud_a llamo compararLen AAAAAAA
    
    .compararLen:
        cmp r13, r14 ; compara la longitud de a y b
        je .retornar_cero ; si longitudes son iguales
        cmp r13, r14
        jb .retornar_uno;si longitud de a < longitud de b significa que tiene menos caracter
        cmp r13, r14
        ja .retornar_menos_uno
        ;cmp r13, r14
    
    .comparar_caracter:
        mov cl, byte[rbx + r15] ; guarda una caracter
        cmp cl , byte[r12 +r15] ; compara posicion r15 de cada cadena
        jb .retornar_uno  ;cuando a[rax] < b[rax]  --> rompen
        cmp cl , byte[r12 +r15] 
        ja .retornar_menos_uno   ;cuando a[rax] > b[rax]  --> rompen 
      
    
    .incrementarCiclo:
        inc r15 ;incremento contador
        jmp .condicion
    
    .retornar_menos_uno:
        mov rax, -1
        jmp .corte
      
    
    .retornar_uno:
        mov rax, 1
        jmp .corte
    

    .retornar_cero:
        mov rax, 0
        jmp .corte

    .corte:
        add rsp, 8
        pop r10
        pop r14
        pop r13
        pop r12
        pop rbx
        pop rbp
        ret


; void strDelete(char* a)
strDelete:
    push rbp
    mov rbp, rsp

    call free

    pop rbp ; recupero el puntero de pila
    ret

; uint32_t strLen(char* a)
strLen:
    push rbp ;alineado
    mov rbp, rsp
    xor rax, rax
    sub rsp, 8; alineado

    .condicion:
        cmp  byte [rax + rdi], 0 ; camparas si el caracter en posicion [rax] es el nulo null == 0 
        je .corte ; si es el nulo salta a corte
    
    .cicloLargo: 
        inc 	rax ; incremento el contador hasta que rax = strlen
        jmp 	.condicion 

    .corte:
        add rsp, 8
        pop rbp ; recupero el puntero de pila
        ret


; ** Array **

; uint8_t arrayGetSize(array_t* a)
arrayGetSize:
    push rbp
    mov rbp, rsp
    mov rax, [rdi + OFFSET_TAMANIO]
    pop rbp
    ret

; void arrayAddLast(array_t* a, void* data)
arrayAddLast: ; agregamos al final si el size < tamaño, clonamos el dato
    push rbp
    mov rbp, rsp
    push rbx ; clonador funcion
    push r10 ; tamanio
    push r12 ;  puntero a dato
    push r13 ; estructura
    push r14 ; capacidad
    xor r10, r10
    push r15 ; dato
    
    .guaradar_parametros:
        mov r13, rdi ; guardo el puntero a la estructura en r13
        mov r15, rsi ; guardo el dato a clonar en r15

    .no_hay_espacio:
        mov r10b, byte[r13 + OFFSET_TAMANIO] ; guardo el size en r10
        mov r14b, byte[r13 + OFFSET_CAPACIDAD] ; guardo la capacidad en r14
        cmp r10b, r14b ; comparo si el size es igual a la capacidad
        jz .cortar

    .obtener_clonador:; pasamos por parametro el tipo y obtenemos el clonador del tipo que estemos 
        mov rdi, [r13 + OFFSET_TIPO] ; guardo el tipo en rdi
        call getCloneFunction
        mov rbx, rax ; -> tipo clonador -> tipo int, tipo string o tipo card -> string 
    
    .clonar:
        mov rdi, r15 ; guardo el dato a clonar en rdi
        call rbx ; llamo al clonador
        mov r15, rax ; guardo el dato clonado en r15 

    .agregar:
        mov r12, [r13 + OFFSET_DATA] ; guardo el puntero a data en r12
        mov [r12 + r10 * 8], r15
        inc r10;
        mov [r13 + OFFSET_TAMANIO], r10b ; guardo el size en la estructura

    .cortar:
        pop r15
        pop r14
        pop r13
        pop r12
        pop r10
        pop rbx
        pop rbp
        ret

; void* arrayGet(array_t* a, uint8_t i)
arrayGet:
    push rbp ;alineado
    mov rbp, rsp
    push r12 ;tamanio - desalineado
    push r13 ;array ded datos -alineado
    push r15 
    xor r15, r15
    sub rsp,8
    
    .obtener_datos:
        movzx r12 , byte[rdi + OFFSET_TAMANIO]
        mov r13,  [rdi + OFFSET_DATA]
        movzx r15, sil

    .comparar_capacidad: ;comparo capacidad  con i para saber si encuentra fuera de rango
        cmp  r12, r15
        jbe .devolver_cero
        cmp  r12, r15
        jae .devolver_data
        
    .devolver_data:
        mov rax ,[r13 + 8*r15]
        jmp .corte
    
    .devolver_cero:
        xor rax, rax

    .corte:
        add rsp,8
        pop r15
        pop r13
        pop r12
        pop rbp
        ret

; array_t* arrayNew(type_t t, uint8_t capacity)
arrayNew:
    push rbp
    mov rbp, rsp

    push r12 ; type_t
    push r13 ; capacidad
    push r14 ; estructura
    sub rsp, 8 ; alineado ;

    ;guardo parametros;
    mov r12d, edi
    mov r13b, sil

    ;pedimos memoria para la estructura;
    mov edi, SIZE_STRUCT_ARRAY
    call malloc
    mov r14, rax

    ; inicializamos type_t, size y capaciadad
    mov [r14 + OFFSET_TIPO], r12d
    mov byte [r14 + OFFSET_TAMANIO], 0
    mov [r14 + OFFSET_CAPACIDAD], r13b
    
    ; pido el espacio para data
    movzx rdi , r13b
    imul rdi, 8 ; multiplicamos rdi por 8 para que sea el tamaño de data
    call malloc
    mov [r14 + OFFSET_DATA], rax
    mov rax, r14
    
    add rsp, 8
    pop r14
    pop r13
    pop r12
    pop rbp
    ret


; void* arrayRemove(array_t* a, uint8_t i)
arrayRemove:
    push rbp ;alineado
    mov rbp, rsp
    push r12 ;tamanio - desalineado
    push r13 ;array ded datos -alineado
    push r14 
    push r15
    push rbx
    xor rbx,rbx
    xor r15,r15
    xor r13,r13
    sub rbp, 8
    
    .obtener_datos:
        mov r14, rdi
        mov r12b , [r14 + OFFSET_TAMANIO]
        mov r13,  [r14 + OFFSET_DATA]
        mov r15b , sil ; i
    
    .comparar_capacidad: ;comparo capacidad  con i para saber si encuentra fuera de rango
        cmp r12b, r15b
        jbe .fuera_rango
        
    .buscar_dato:
        mov rax ,[r13 + 8*r15]
    
    .comparar:
        inc r15
        cmp r15b, r12b
        jne .reacomodar
        jmp .bajar_cantidad
    

    .reacomodar:
        cmp r15b , r12b
        jae .bajar_cantidad 
        mov ebx, [r13 +  8*r15]
        mov [r13 +  (8*r15 - 8)], ebx
        inc r15
        jmp .reacomodar

    .bajar_cantidad:
        dec r12
        mov [r14 + OFFSET_TAMANIO], r12b
        jmp .corte

    .fuera_rango:
        mov rax, 0
        jmp .corte
    
    .corte:
        add rbp, 8
        pop rbx
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret


; void arraySwap(array_t* a, uint8_t i, uint8_t j)
arraySwap:
    push rbp
    mov rbp, rsp

    push r12 ;arr
    push r13 ; size

    xor r13, r13
    xor r8, r8 
    xor r9, r9

    .guardar_datos:
        mov r12, rdi
        mov r13d, [rdi + OFFSET_TAMANIO]
        mov r8b, sil
        mov r9b, dl

    .comparar:
        cmp r8b, r9b
        je .corte

        cmp r8b, r13b
        jae .corte

        cmp r9b, r13b
        jae .corte

    .swap:
        mov r12, [rdi + OFFSET_DATA]
        mov r10, [r12 + 8 * r8]
        mov r11, [r12 + 8 * r9]

        mov [r12 + 8 * r8], r11
        mov [r12 + 8 * r9], r10

    .corte:
        pop r13
        pop r12
        pop rbp
        ret

; void arrayDelete(array_t* a)
arrayDelete:
    push rbp
    mov rbp, rsp
    push r12 ;array
    push r13 ; contador
    push r14 ; getDeleteFunction
    sub rsp, 8
    xor r13, r13

    .inicializamos:
        mov r12, rdi ; movemos el struct a r12
        mov r13b, byte[r12 + OFFSET_TAMANIO] ; movemos el tamanio
        mov edi, [r12 + OFFSET_TIPO]
        call getDeleteFunction
        mov r14, rax       

    .esta_vacio:
        test r13d, r13d ; 
        jz .borrar_estructura
    
    .hay_elementos:
        dec r13
        mov rdi, r12
        mov rsi, r13
        call arrayRemove
        mov rdi, rax
        call r14
        jmp .esta_vacio
    
    .borrar_estructura:
        mov rdi, [r12 + OFFSET_DATA]
        call free
        mov rdi, r12
        call free
    
    .corte:
        add rsp, 8
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

;void arrayPrint(array_t* a, FILE* pFile)
arrayPrint: 
    push rbp
    mov rbp, rsp

    push r12 ; array
    push r13 ; file
    push r14 ; contador
    push r15 ; print

    
    xor r14, r14
    mov r12, rdi
    mov r13, rsi

    mov edi, [r12 + OFFSET_TIPO]
    call getPrintFunction
    mov r15, rax

    .imprimir_apertura:
        mov rdi, rsi ; guardo el archivo en rdi
        mov rsi, corchete_abierto ; guardo la palabra en rsi
        call fprintf
        
    .comparar_size:
        xor rcx, rcx
        mov cl, [r12 + OFFSET_TAMANIO]
        cmp rcx, r14
        jz .imprimir_cierre

    .ciclo_print: 
        mov r8, [r12 + OFFSET_DATA]
        mov rdi, [r8 + 8 * r14]
        mov rsi, r13
        call r15
        inc r14
        xor rcx, rcx
        mov cl, [r12 + OFFSET_TAMANIO]
        cmp rcx, r14
        jz .imprimir_cierre
    
    .imprimir_coma:
        mov rdi, r13 ; guardo el archivo en rdi
        mov rsi, coma_array ; guardo la palabra en rsi
        call fprintf
        jmp .comparar_size

    .imprimir_cierre:
        mov rdi, r13 ; guardo el archivo en rdi
        mov rsi, corchete_cerrado ; guardo la palabra en rsi
        call fprintf

    .termino:
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

; ** Card **

; card_t* cardNew(char* suit, int32_t* number)
cardNew:
    push rbp
    mov rbp, rsp

    push r12
    push r13
    push r14
    sub rsp, 8
    
    xor r12, r12
    xor r13, r13
    xor r14, r14

    .guaradar_parametros:
        mov r12, rdi
        mov r13, rsi
        
    .inicializo_estructura:
        mov edi, SIZE_CARD
        call malloc
        mov r14, rax

    .inicializo_palo:
        mov rdi, r12
        call strClone
        mov [r14], rax

    .inicializo_number:
        mov rdi, r13
        call intClone
        mov [r14 + OFFSET_NUMBER], rax

    .inicializo_lista:
        mov edi, TYPE_CARD
        call listNew
        mov [r14 + OFFSET_STACKED], rax

    .corte:
        mov rax, r14
        add rsp, 8
        pop r14
        pop r13
        pop r12
        pop rbp    
        ret

;char* cardGetSuit(card_t* c)
cardGetSuit:
    push rbp
    mov rbp, rsp
    
    mov rax,[rdi + OFFSET_SUIT]

    pop rbp
    ret

;int32_t* cardGetNumber(card_t* c)
cardGetNumber:
    push rbp
    mov rbp, rsp
    
    mov rax,[rdi + OFFSET_NUMBER]

    pop rbp
    ret

;list_t* cardGetStacked(card_t* c)
cardGetStacked:
    push rbp
    mov rbp, rsp
    
    mov rax,[rdi + OFFSET_STACKED]

    pop rbp
    ret

;void cardPrint(card_t* c, FILE* pFile)
cardPrint:
    push rbp
    mov rbp, rsp

    push r12
    push r13

    mov r12, rdi ;card
    mov r13, rsi ;file

    .apertura:
        mov rdi, rsi ; guardo el archivo en rdi
        mov rsi, llaveAbierta_str; guardo la palabra en rsi
        call fprintf


    .imprimir_palo:
        mov rdi, r12
        call cardGetSuit
        mov rdi, rax
        mov rsi, r13
        call strPrint

    .imprimir_guion:
        mov rdi, r13
        mov rsi, guion_str
        call fprintf

    .imprimir_numero:
        mov rdi, r12
        call cardGetNumber
        mov rdi, rax
        mov rsi, r13
        call intPrint

    .imprimir_guion2:
        mov rdi, r13
        mov rsi, guion_str
        call fprintf
    
    .imprimir_lista:
        mov rdi, r12
        call cardGetStacked
        mov rdi, rax
        mov rsi, r13
        call listPrint
        
    
    .cerrar:
        mov rdi, r13; guardo el archivo en rdi
        mov rsi, llaveCerrada_str ; guardo la palabra en rsi
        call fprintf
    
    .corte:
        pop r13
        pop r12
        pop rbp
        ret

;int32_t cardCmp(card_t* a, card_t* b)
cardCmp:
    push rbp
    mov rbp, rsp

    push r12 ; a
    push r13 ; b
    push r14 ; palo a
    sub rsp, 8

    .guardado:
        mov r12, rdi
        mov r13, rsi

    .comparar_palo:
        call cardGetSuit
        mov r14, rax

        mov rdi, r13
        call cardGetSuit
        mov rsi, rax

        mov rdi, r14
        call strCmp

        test rax, rax ; es un and
        jz .comparar_numero
        jmp .corte

    .comparar_numero:
        mov rdi, r12
        call cardGetNumber
        mov r14, rax

        mov rdi, r13
        call cardGetNumber
        mov rsi, rax

        mov rdi, r14
        call intCmp

    .corte:
        add rsp, 8;
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

;card_t* cardClone(card_t* c)
cardClone:
    push rbp
    mov rbp, rsp

    push r12 ; para c
    push r13 ; para clon 

    mov r12, rdi ; me guardo c
    
    mov rdi, SIZE_CARD ; pido memoria para el clon
    call malloc
    mov r13, rax

    mov rdi, r12
    call cardGetSuit
    mov rdi, rax
    call strClone
    mov [r13 + OFFSET_SUIT] , rax

    mov rdi, r12
    call cardGetNumber
    mov rdi, rax
    call intClone
    mov [r13 + OFFSET_NUMBER], rax


    mov rdi, r12
    call cardGetStacked
    mov rdi, rax
    call listClone
    mov [r13 + OFFSET_STACKED], rax

    mov rax, r13

    pop r13
    pop r12
    pop rbp
    ret

;void cardAddStacked(card_t* c, card_t* card)
cardAddStacked:
    push rbp
    mov rbp, rsp

    push r12
    push r13

    mov r12, rsi
    call cardGetStacked
    mov rdi, rax
    mov rsi, r12
    call listAddFirst

    pop r13
    pop r12
    pop rbp
    ret

;void cardDelete(card_t* c)
cardDelete:
    push rbp
    mov rbp, rsp
    push r12 ; estructura
    push r13 ; palo
    push r14 ; numero
    push r15 ; listas
    xor r12,r12
    xor r13,r13
    xor r14,r14
    xor r15,r15


    .guardo_parametro:
        mov r12, rdi ; guarda estructura 
        mov r13, [r12 ] ; guarda palo
        mov r14, [r12 + OFFSET_NUMBER] ; guarda numero
        mov r15, [r12 + OFFSET_STACKED] ; guarda  lista
        
    .borrar_palo:
        mov rdi, r13
        call strDelete
        jmp .borrar_numero

    .borrar_numero:
        mov rdi, r14
        call intDelete
        jmp .borrar_lista

    .borrar_lista:
        mov rdi, r15
        call listDelete
        jmp .borrar_estructura

    .borrar_estructura:    
        mov rdi, r12
        call free
        jmp .corte

    .corte:
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret