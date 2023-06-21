#ifndef CODES
#define CODES
// para incluir codes.h apenas uma vez e não acontecer redefinicão de tipos

typedef enum return_codes
{
    ok,
    formato_invalido,
    erro_alocacao,
    ok_vazio,
    ok_jogo_nao_encontrado,
    formato_invalido_dia_entre_1_e_31,
    formato_invalido_mes_entre_1_e_12,
    formato_invalido_ano_maior_que_0,
    formato_invalido_fevereiro_tem_28_dias,
    formato_invalido_meses_4_6_9_11_nao_possuem_dia_31,
    formato_invalido_dia_28_de_fevereiro_somente_existe_em_anos_bissextos,
    formato_invalido_ano_deve_possuir_quatro_digitos,
    formato_invalido_quantidade_negativa,
    ok_quantidade_insuficiente,
} ReturnCode;

#endif