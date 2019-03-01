all: ud_ucase_sv ud_ucase_cl

ud_ucase_sv: ud_ucase_sv.c 
        @gcc -W -o ud_ucase_sv ud_ucase_sv.c

ud_ucase_cl: ud_ucase_cl.c
        @gcc -W -o ud_ucase_cl ud_ucase_cl.c

clean:
        @rm -f ud_ucase_sv ud_ucase_cl
