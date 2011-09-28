<?php

/**
 * @file
 * Functions relating to admin settings
 */

/**
 * Form for configuring various settings
 */
function ccb_auth_admin_form($form, &$form_state) {
  $form['checks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dependency tests'),
  );
  
  $ssl = extension_loaded('openssl') ? '<span style="color: green">OK</span>' : '<span style="color: red">ERROR</span>';
  $form['checks']['ssl'] = array(
    '#type' => 'item',
    '#markup' => 'PHP OpenSSL extension: '.$ssl,
  );
  
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API Settings'),
  );
  
  $form['api']['ccb_auth_url'] = array(
    '#type' => 'textfield',
    '#title' => t('API URL'),
    '#description' => t('API URL without the protocol e.g. mychurch.ccbchurch.com/api.php'),
    '#default_value' => variable_get('ccb_auth_url'),
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  
  $form['api']['ccb_auth_user'] = array(
    '#type' => 'textfield',
    '#title' => t('API User Name'),
    '#default_value' => variable_get('ccb_auth_user'),
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  
  $form['api']['ccb_auth_pass'] = array(
    '#type' => 'textfield',
    '#title' => t('API Password'),
    '#default_value' => variable_get('ccb_auth_pass'),
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  
  $form['groups'] = array(
    '#type' => 'fieldset',
    '#title' => t('Group/Role associations'),
  );
  
  $form['groups']['ccb_auth_groups'] = array(
    '#type' => 'textfield',
    '#title' => t('Group/Role pairs'),
    '#description' => t('Format: ccb_group_id,drupal_role_id;ccb_group_id,drupal_role_id'),
    '#default_value' => variable_get('ccb_auth_groups'),
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  
  return system_settings_form($form);
}