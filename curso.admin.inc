<?php

/**
 * Carrega o formulário de configuração baseado em chamda do menu.
 *
 * Essa função é um callback para a função drupal_get_form no menu
 *
 * @param $form
 *   Formulário em si
 * @param $form_state
 *   Dados processado pelo formulário, geralmente usado em caso de erro.
 */
function curso_config($form, &$form_state) {

  $form['papeis'] = array(
    '#type' => 'textarea',
    '#title' => t('Papéis na Bovespa'),
    '#description' => t('Digite os papeis na Bovespa, um por linha. Exemplo: VALE3'),
    '#required' => TRUE,
    '#default_value' => variable_get('curso_bovespa_papeis',  ''),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Salvar"),
  );
  return $form;
}

/**
 * Toda função processada com drupal_get_form aceita um validate
 *
 * Essa função é responsável pela validação do formulário
 *
 * @param $form
 *   Formulário em si
 * @param $form_state
 *   Dados submetidos
 */
function curso_config_validate($form, &$form_state) {
  $papel = $form_state['values']['papeis'];
  if (strtoupper($papel) == 'VALE3') {
    form_set_error('papel', t('VALE3 é considerado inválido.'));
  }
}

/**
 * Toda função processada com drupal_get_form tem um submit
 *
 * Essa função é irá pegar os valores submetidos e tratar adequadamente
 *
 * @param $form
 *   Formulário em si
 * @param $form_state
 *   Dados submetidos
 */
function curso_config_submit($form, &$form_state) {
  $papeis = strtoupper($form_state['values']['papeis']);
  variable_set('curso_bovespa_papeis', $papeis);
  drupal_set_message(t('Os papéis @papel foram salvos', array('@papel' => implode(",", explode("\n", $papeis) ))));
  // limpando o cache para forçar um reload.
  cache_clear_all('curso_papeis_cache', 'cache');
}
