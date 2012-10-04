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

  $form['papel'] = array(
    '#type' => 'textfield',
    '#title' => t('Papel na Bovespa'),
    '#description' => t('Digite um papel da Bovespa. Exemplo: VALE3'),
    '#required' => TRUE,
    '#default_value' => variable_get('curso_bovespa_papel',  ''),
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
  $papel = $form_state['values']['papel'];
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
  $papel = strtoupper($form_state['values']['papel']);
  variable_set('curso_bovespa_papel', $papel);
  drupal_set_message(t('O papel @papel foi salvo', array('@papel' => $papel)));
  // limpando o cache para forçar um reload.
  cache_clear_all('curso_papel_cache', 'cache');
}
