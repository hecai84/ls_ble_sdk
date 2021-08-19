#ifndef _AT_SIG_MESH_PROVER_CMD_IND_H_
#define _AT_SIG_MESH_PROVER_CMD_IND_H_

#include "platform.h"
#include "modem_rf_le501x.h"
#include "ls_ble.h"
/**
 * @brief 
 * 
 */
void at_prover_ready_ind(void);
/**
 * @brief 
 * 
 * @param param 
 */
void at_prover_report_dev_uuid(uint8_t *param);
/**
 * @brief 
 * 
 * @param status
 * @param node_unicast_addr
 */
void at_prover_report_provisiong_status(uint8_t status,uint16_t node_unicast_address);

/**
 * @brief 
 * 
 * @param unicast_addr
 * @param company_id
 * @param product_id
 * @param version_id
 * @param support_feature
 * @param dev_nb_elements
 */
void at_prover_report_dev_composition_data0(uint16_t unicast_addr,uint16_t company_id, uint16_t product_id,uint16_t version_id, uint16_t support_feature, uint8_t dev_nb_elements);
/**
 * @brief 
 * 
 * @param element_addr
 * @param number_sig_models
 * @param number_vendor_models
 * @param model_info
 */
void at_prover_report_dev_composition_data0_element(uint16_t element_addr,uint8_t number_sig_models, uint8_t number_vendor_models,uint8_t *model_info);
/**
 * @brief 
 * 
 * @param unicast_addr
 * @param default_ttl
 */
void at_prover_report_dev_default_ttl(uint16_t unicast_addr,uint8_t default_ttl);
/**
 * @brief 
 * 
 * @param unicast_addr
 * @param act_status
 * @param net_key_id
 * @param app_key_id
 */
void at_prover_report_node_app_key_status(uint16_t unicast_addr,uint8_t act_status,uint16_t net_key_id,uint8_t app_key_id);
/**
 * @brief Construct a new at prover report model subs status object
 * 
 * @param unicast_addr
 * @param subs_status
 * @param element_addr
 * @param model_id
 * @param subs_value
 */
void at_prover_report_model_subs_status(uint16_t unicast_addr,uint8_t subs_status,uint16_t element_addr,uint32_t model_id,uint16_t subs_value);
/**
 * @brief 
 * 
 * @param unicast_addr
 * @param model_app_status
 * @param element_addr
 * @param model_id
 * @param model_app_value
 */
void at_prover_report_model_app_status(uint16_t unicast_addr,uint8_t model_app_status,uint16_t element_addr,uint32_t model_id,uint16_t model_app_value);
#endif // _AT_SIG_MESH_PROVER_CMD_IND_H_
