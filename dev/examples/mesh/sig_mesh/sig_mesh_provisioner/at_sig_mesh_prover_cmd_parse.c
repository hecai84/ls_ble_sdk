#include "stdlib.h"
#include "string.h"
#include "at_sig_mesh_prover_recv_cmd.h"
#include "at_sig_mesh_prover_cmd_parse.h"
#include "ls_sig_mesh_provisioner.h"
#include "sig_mesh_prover_ctl.h"
#include "log.h"
/**
 * @brief 
 * 
 * @param p_cmd_parse 
 */
static void at_add_dev_uuid(uint8_t *p_cmd_parse);

static void at_start_scan(uint8_t *p_cmd_parse);

static void at_start_invite(uint8_t *p_cmd_parse);

static void at_stop_scan(uint8_t *p_cmd_parse);

static void at_bind_model_app(uint8_t *p_cmd_parse);

static void at_unbind_model_app(uint8_t *p_cmd_parse);

static void at_generic_onoff_model_app(uint8_t *p_cmd_parse);
#if 0
static void at_add_dev_key(uint8_t *p_cmd_parse);

static void at_add_net_key(uint8_t *p_cmd_parse);

static void at_use_new_net_key(uint8_t *p_cmd_parse);

static void at_revoke_old_net_key(uint8_t *p_cmd_parse);

static void at_del_net_key(uint8_t *p_cmd_parse);

static void at_update_net_key(uint8_t *p_cmd_parse);

static void at_config_client_active_net_key(uint8_t *p_cmd_parse);

static void at_add_app_key(uint8_t *p_cmd_parse);

static void at_del_app_key(uint8_t *p_cmd_parse);

static void at_update_app_key(uint8_t *p_cmd_parse);

static void at_config_client_active_app_key(uint8_t *p_cmd_parse);

static void at_config_dev(uint8_t *p_cmd_parse);

static void at_get_model_info(uint8_t *p_cmd_parse);

static void at_act_model_subs(uint8_t *p_cmd_parse);

static void at_set_model_publi(uint8_t *p_cmd_parse);

static void at_config_client_set(uint8_t *p_cmd_parse);

static void at_config_client_get(uint8_t *p_cmd_parse);

static void at_config_client_set_heartbeat_publication(uint8_t *p_cmd_parse);

static void at_config_client_set_heartbeat_subscription(uint8_t *p_cmd_parse);

static void at_get_healthc(uint8_t *p_cmd_parse);

static void at_set_healthc(uint8_t *p_cmd_parse);

static void at_healthc_active_fault(uint8_t *p_cmd_parse);

static void at_config_reg_model(uint8_t *p_cmd_parse);

static void at_health_reg_model(uint8_t *p_cmd_parse);
#endif
typedef void (*at_cmd_handler_t)(uint8_t *p_cmd_parse);
/**
 * @struct
 * 
 */
typedef struct
{
    char              *cmd_tag_str; 
    uint8_t            cmd_tag_length;
    at_cmd_handler_t   cmd_handler;
} at_cmd_attr_t;

/**
 * @brief 
 * 
 */
static const at_cmd_attr_t at_cmd_attr_table[] =
{
    {"START_SCAN",                 10, at_start_scan},
    {"ADD_DEV_UUID",               12, at_add_dev_uuid},
    {"START_INVITE",               12, at_start_invite},   
    {"STOP_SCAN",                   9, at_stop_scan},
    {"BIND_MDL_APP",               12, at_bind_model_app},
    {"UNBIND_MDL_APP",             14, at_unbind_model_app},
    {"ONOFF_MDL_APP",              13, at_generic_onoff_model_app},
     #if 0  
    {"ADD_DEVKEY",                 11, at_add_dev_key},
    {"ADD_NETKEY",                 11, at_add_net_key},
    {"USE_NEW_NETKEY",             14, at_use_new_net_key},
    {"REV_OLD_NETKEY",             14, at_revoke_old_net_key},
    {"DEL_NETKEY",                 10, at_del_net_key},
    {"UPDATE_NETKEY",              13, at_update_net_key},
    {"ACT_NETKEY",                 10, at_config_client_active_net_key},
    {"ADD_APPKEY",                 10, at_add_app_key},
    {"DEL_APPKEY",                 10, at_del_app_key},
    {"UPDATE_APPKEY",              13, at_update_app_key},
    {"ACT_APPKEY",                 10, at_config_client_active_app_key},
    {"CONF_DEV",                    8, at_config_dev},
    {"GET_MDL_INFO",               12, at_get_model_info},
    {"ACT_MDL_SUBS",               12, at_act_model_subs},
    {"SET_MDL_PUBLI",              13, at_set_model_publi},
    {"CONF_CLI_SET",               12, at_config_client_set},
    {"CONF_CLI_GET",               12, at_config_client_get},
    {"SET_HB_PUBLI",               12, at_config_client_set_heartbeat_publication},
    {"SET_HB_SUBS",                11, at_config_client_set_heartbeat_subscription},
    {"GET_HTHC",                   8, at_get_healthc},
    {"SET_HTHC",                   8, at_set_healthc},
    {"ACT_HTHC_FLT",               12, at_healthc_active_fault},
    {"CONF_REG_MDL",               14, at_config_reg_model},
    {"HTH_REG_MDL",                11, at_health_reg_model},
#endif    
};

static uint8_t dev_uuid[16]={0};

uint8_t *find_int_from_str(uint8_t *buff)
{
    uint8_t *pos = buff;
    while (1)
    {
        if (*pos == ',' || *pos == '\r'){
            *pos = 0;
            break;
        }
        pos++;
    }
    return pos;
}

void str_to_hex_arr(uint8_t* hex_arr, uint8_t *str, uint8_t arr_len)
{
    for (uint8_t i = 0; i < arr_len; i++)
    {
        if ((str[i * 2] <= '9') && (str[i * 2] >= '0'))
            hex_arr[i] = (str[i * 2] - '0') * 16;
        else if ((str[i * 2] <= 'f') && (str[i * 2] >= 'a'))
            hex_arr[i] = (str[i * 2] - 'a' + 10) * 16;
        else if ((str[i * 2] <= 'F') && (str[i * 2] >= 'A'))
            hex_arr[i] = (str[i * 2] - 'A' + 10) * 16;

        if ((str[i * 2 + 1] <= '9') && (str[i * 2 + 1] >= '0'))
            hex_arr[i] += (str[i * 2 + 1] - '0');
        else if ((str[i * 2 + 1] <= 'f') && (str[i * 2 + 1] >= 'a'))
            hex_arr[i] += (str[i * 2 + 1] - 'a' + 10);
        else if ((str[i * 2 + 1] <= 'F') && (str[i * 2 + 1] >= 'A'))
            hex_arr[i] += (str[i * 2 + 1] - 'A' + 10);
    }
}

void hex_arr_to_str(uint8_t *str, const uint8_t hex_arr[], uint8_t arr_len)
{
    for (int16_t i = arr_len-1; i >=0; i--)
    {
        sprintf((char *)(str + (arr_len -1 -i) * 2), "%02X", hex_arr[i]);
    }
}

void at_recv_cmd_handler(at_recv_cmd_t *param)
{
    uint8_t cmd_num = sizeof(at_cmd_attr_table) / sizeof(at_cmd_attr_t);
    uint8_t *buff = param->recv_data;
    for(uint8_t i=0;i<cmd_num;i++) {
        if(memcmp(buff, at_cmd_attr_table[i].cmd_tag_str,at_cmd_attr_table[i].cmd_tag_length) == 0){
            buff += strlen(at_cmd_attr_table[i].cmd_tag_str);
            at_cmd_attr_table[i].cmd_handler(buff);
        }
    }
}

static void at_start_scan(uint8_t *p_cmd_parse)
{
    uint16_t scan_timeout=0;
    if ((*p_cmd_parse++) ==  '=')
     {
       str_to_hex_arr((uint8_t *)&scan_timeout, p_cmd_parse, sizeof(uint16_t));
       ls_sig_mesh_provisioner_scan(scan_timeout);
        
     }  
}

static void at_add_dev_uuid(uint8_t *p_cmd_parse)
{
     if ((*p_cmd_parse++) ==  '=')
     {
        str_to_hex_arr(dev_uuid, p_cmd_parse, UUID_MESH_DEV_LEN);
        LOG_I("uart_rx_dev_uuid");
        LOG_HEX(&dev_uuid[0],16);
     }  
}

static void at_start_invite(uint8_t *p_cmd_parse)
{
    uint8_t invite_uuid[UUID_MESH_DEV_LEN]={0};

    if ((*p_cmd_parse++) ==  '=')
     {
       str_to_hex_arr(invite_uuid, p_cmd_parse, UUID_MESH_DEV_LEN);
       LOG_I("invite_uuid");
       LOG_HEX(&invite_uuid[0],16);
       ls_sig_mesh_provisioner_invite(CONNECT_IDX_INVALID/*connect_id*/,&invite_uuid[0],0/*attention_s 0:attention_off*/);
     }
}

static void at_stop_scan(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_provisioner_stop();
}

static void at_bind_model_app(uint8_t *p_cmd_parse)
{
     uint16_t element_addr=0;
     uint16_t appkey_id=0;
     uint32_t model_id=0;
     uint8_t offset=0;
   if ((*p_cmd_parse++) ==  '=')
   { 
        str_to_hex_arr((uint8_t *)&element_addr, p_cmd_parse+offset, sizeof(uint16_t));
        offset = 2*sizeof(uint16_t)+1;
        str_to_hex_arr((uint8_t *)&appkey_id, p_cmd_parse+offset, sizeof(uint16_t));
        offset += 2*sizeof(uint16_t)+1;
        str_to_hex_arr((uint8_t *)&model_id, p_cmd_parse+offset, sizeof(uint32_t));
        ls_sig_mesh_prover_config_client_act_model_app(0/*bind model app key*/,element_addr,appkey_id,model_id); 
   }
}

static void at_unbind_model_app(uint8_t *p_cmd_parse)
{
     uint16_t element_addr=0;
     uint16_t appkey_id=0;
     uint32_t model_id=0;
     uint8_t offset=0;
   if ((*p_cmd_parse++) ==  '=')
   { 
        str_to_hex_arr((uint8_t *)&element_addr, p_cmd_parse+offset, sizeof(uint16_t));
        offset = 2*sizeof(uint16_t)+1;
        str_to_hex_arr((uint8_t *)&appkey_id, p_cmd_parse+offset, sizeof(uint16_t));
        offset += 2*sizeof(uint16_t)+1;
        str_to_hex_arr((uint8_t *)&model_id, p_cmd_parse+offset, sizeof(uint32_t));
        ls_sig_mesh_prover_config_client_act_model_app(1/*ubind model app key*/,element_addr,appkey_id,model_id); 
   }
}

static void at_generic_onoff_model_app(uint8_t *p_cmd_parse)
{
     uint32_t tx_message=0;
     uint16_t dest_addr=0;
     uint32_t model_id=0;
     uint8_t offset=0;
   if ((*p_cmd_parse++) ==  '=')
   { 
        str_to_hex_arr((uint8_t *)&tx_message, p_cmd_parse+offset, sizeof(uint32_t));
        offset = 2*sizeof(uint32_t)+1;
        str_to_hex_arr((uint8_t *)&dest_addr, p_cmd_parse+offset, sizeof(uint16_t));
        offset += 2*sizeof(uint16_t)+1;
        str_to_hex_arr((uint8_t *)&model_id, p_cmd_parse+offset, sizeof(uint32_t));
        prover_client_model_tx_message_handler(tx_message, dest_addr, model_id);
   }
}
#if 0
static void at_add_net_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_provisioner_add_net_key();/**< netkey_id / net_key*/
}

static void at_add_dev_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_provisioner_add_dev_key();/**< address / dev_key*/
}

static void at_use_new_net_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_provisioner_use_new_net_key();/**< netkey_id*/
}

static void at_revoke_old_net_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_provisioner_revoke_old_net_key();/**< netkey_id*/
}

static void at_del_net_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_provisioner_delete_net_key();/**< netkey_id*/
}

static void at_update_net_key(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_provisioner_update_net_key();/**< netkey_id / net_key*/
}

static void at_config_client_active_net_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_prover_config_client_active_netkey();/**<act_netkey_type/net_key_id/data/data_len */
}

static void at_add_app_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_provisioner_add_app_key();/**< netkey_id/appkey_id / net_key*/
}

static void at_del_app_key(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_provisioner_delete_app_key();/**< netkey_id/appkey_id*/
}

static void at_update_app_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_provisioner_update_app_key();/**< netkey_id/appkey_id / net_key*/
}
static void at_config_client_active_app_key(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_prover_config_client_active_appkey();/**<act_appkey_type/ net_key_id /app_key_id/appkey*/
}

static void at_config_dev(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_prover_config_set_dev(); /**< dev_key_lid/net_key_lid / primary_addr*/
}

static void at_get_model_info(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_prover_config_client_get_model(); /**< get_model_type/element_address/model_id*/
}

static void at_act_model_subs(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_prover_config_client_act_model_subscript();/**<model_subscript_act_type/element_address/model_id/address_type/length/address_uuid*/
}

static void at_set_model_publi(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_prover_config_client_set_model_publication();/**<addr_type/element_addr/appkey_id/cred_flag/pub_ttl/pub_period/retx_cnt/retx_intv_slots/mdl_id/length/val*/
}

static void at_config_client_set(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_prover_config_client_set();/**<set_type/value/tx_cnt/intv_slots*/
}

static void at_config_client_get(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_prover_config_client_get();/**<get_type/value*/
}

static void at_config_client_set_heartbeat_publication(uint8_t *p_cmd_parse)
{
  void ls_sig_mesh_prover_config_client_set_heartbeat_publication();/**<dst/cnt/ttl/features/nekkey_id*/
}

static void at_config_client_set_heartbeat_subscription(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_prover_config_client_set_heartbeat_subscription();/**<src/dst/period_s*/
}

static void at_get_healthc(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_prover_health_client_get();/**<address/appkey_lid/get_type/company_id*/
}

static void at_set_healthc(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_prover_health_client_set();/**<address/appkey_lid/set_type/set_cfg/val*/
}

static void at_healthc_active_fault(uint8_t *p_cmd_parse)
{
  ls_sig_mesh_prover_health_client_act_fault();/**<address/appkey_lid/act_type/act_cfg/set_type/test_id/company_id*/
}

static void at_config_reg_model(uint8_t *p_cmd_parse)
{
    ls_sig_mesh_prover_config_reg_model();
}

static void at_health_reg_model(uint8_t *p_cmd_parse)
{
   ls_sig_mesh_prover_health_client_reg_model();
}
#endif
