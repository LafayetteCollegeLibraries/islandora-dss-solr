<?php

  /**
   * @files
   *
   */

/**
 * AJAX callback for advanced search form
 *
 * @param type $form
 * @param type $form_state
 * @return type
 *
 * @see islandora_solr_advanced_search_form()
 */
function _islandora_dss_solr_advanced_search_terms($form, &$form_state) {

  return $form['terms'];
}

/**
 * Islandora Solr advanced search block form
 * @author griffinj@lafayette.edu
 *
 * @see islandora_solr_advanced_search_form($form, &$form_state)
 *
 * @global type $_islandora_solr_queryclass
 *   the IslandoraSolrQueryProcessor object which includes the current query
 *   settings and the raw Solr results.
 * @param type $form
 * @param array $form_state
 * @return string
 */
function islandora_dss_solr_advanced_search_form($form, &$form_state) {

  drupal_add_library('system', 'ui.tabs');

  global $_islandora_solr_queryclass;

  // include common.inc
  module_load_include('inc', 'islandora_solr', 'includes/common');

  // check form states
  // 1. form update using ajax
  // 2. populate with current query on search results page
  // 3. anywhere else: empty form

  // 1. form update using ajax
  if (isset($form_state['triggering_element'])) {

    // unset terms from input array
    // http://drupal.stackexchange.com/questions/14855/how-do-i-dynamically-fill-a-textfield-with-ajax/16576#16576
    unset($form_state['input']['terms']);

    // check for add
    //if ($form_state['triggering_element']['#value'] == '+') {
    if (preg_match('/add\-field/', $form_state['triggering_element']['#name'])) {

      //$form_state['values']['terms'][] = array();
      //} elseif ($form_state['triggering_element']['#value'] == '-') { // check for remove
    } elseif (preg_match('/remove\-field/', $form_state['triggering_element']['#name'])) { // check for remove

      $field = $form_state['triggering_element']['#field'];
      array_splice($form_state['values']['terms'], $field, 2);
    }

    // set values
    $values = $form_state['values'];

    //dpm($values);
  } elseif (islandora_solr_results_page($_islandora_solr_queryclass) == TRUE && !isset($_islandora_solr_queryclass->internalSolrParams['type'])) {

    // 2. populate with current query on search results page

    // get current query
    $query = $_islandora_solr_queryclass->solrQuery;
    // set value variable
    $values['terms'] = array();

    // explode on space
    $query_explode = explode(' ', $query);

    // break up the solr query to populate the advanced search form
    $i = 0;
    foreach ($query_explode as $key => $value) {

      $term = array();

      // check for first colon to split the string
      if (strpos($value, ':') != FALSE) {

        // split the filter into field and value
        $value_split = explode(':', $value, 2);
        // set field
        $values['terms'][$i]['field'] = $value_split[0];

        // second part of the split is the query value (or first part of it)
        $value_split[1] = str_replace(array('(', ')'), '', $value_split[1]);
        // add search string
        $values['terms'][$i]['search'] = $value_split[1];
      }
      // if the string does not include a colon or AND/OR/NOT, then it is a
      // part of the query value
      elseif (!preg_match('/(AND|OR|NOT)/', $value, $matches)) {
        // trim brackets
        $value = str_replace(array('(', ')'), '', $value);

        if (isset($values['terms'][$i]['search'])) {
          // append to search string
          $values['terms'][$i]['search'] .= ' ' . $value;
        }
        else {
          // search field is not set, so create new search value
          $values['terms'][$i]['search'] = $value;
        }
      }
      // if it matches AND/OR/NOT, then we have the boolean operator
      else {
        // set boolean operator
        $values['terms'][$i]['boolean'] = $value;

        // increment to next field
        $i++;
      }
    }
  }
  // 3. anywhere else: empty form
  else {
    //Need at least one term to draw the search box.
    $values = array(
      'terms' => array(''),
    );
  }

  $terms = array(
    '#type' => 'markup',
    '#prefix' => '<div id="islandora-solr-advanced-terms">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  // loop over each term
  foreach ($values['terms'] as $i => $value) {

    $term = array('#tree' => TRUE,
		  //'#class' => array('islandora-solr-advanced-term'),
		  '#prefix' => '<div class="islandora-solr-advanced-term">',
		  '#suffix' => '</div>');

    $term['field-wrapper'] = array('#type' => 'fieldset');

    /*
    $term['field'] = array(
      '#title' => t(''),
      '#type' => 'select',
      '#default_value' => isset($value['field']) ? $value['field'] : 'dc.title',
      '#options' => islandora_solr_get_fields('search_fields'),
      '#attributes' => array('class' => array('islandora-solr-search-field')));

    $term['search'] = array(
			    '#title' => t(''),
			    '#type' => 'textfield',
			    '#size' => 20,
			    '#default_value' => isset($value['search']) ? $value['search'] : 'Search...',
			    );

    $term['hidden_submit'] = array(// Used for when the user presses enter on the search field.

      '#type' => 'submit',
      '#value' => t('Search'),
      '#attributes' => array('style' => 'visibility:hidden;position:fixed;top:-1000px;right:-1000px;')
    );
    */

    $term['field-wrapper']['field'] = array(
      '#title' => t(''),
      '#type' => 'select',
      '#default_value' => isset($value['field']) ? $value['field'] : 'dc.title',
      '#options' => islandora_solr_get_fields('search_fields'),
      '#attributes' => array('class' => array('islandora-solr-search-field')));

    $term['field-wrapper']['search'] = array(
			    '#title' => t(''),
			    '#type' => 'textfield',
			    '#size' => 80,
			    '#default_value' => isset($value['search']) ? $value['search'] : '',
			    );

    // Used for when the user presses enter on the search field.
    $term['field-wrapper']['hidden_submit'] = array(
						    '#type' => 'submit',
						    '#value' => t('Search'),
						    '#attributes' => array('style' => 'visibility:hidden;position:fixed;top:-1000px;right:-1000px;')
						    );

    /*
    if(count($values['terms']) < 5) {

      $term['add'] = array(
			   '#type' => 'button',
			   '#value' => '+',
			   '#attributes' => array('title' => t('Add a field'),
						  'class' => array('islandora-solr-search-add')),
			   '#name' => 'add-field-' . $i,
			   '#ajax' => array(
					    'callback' => '_islandora_solr_advanced_search_terms',
					    'wrapper' => 'islandora-solr-advanced-terms',
					    'method' => 'replace',
					    'effect' => 'fade',
					    'progress' => array('type' => 'none'),
					    ),
			   '#suffix' => '<button type="islandora-solr-search-add"><i class="icon-large icon-plus-sign"></i></button>',
			   );
    }
    */

    if (count($values['terms']) > 1) {

      //$term['remove'] = array(
      $term['field-wrapper']['remove'] = array(

        '#type' => 'button',
        '#field' => $i,
        '#value' => '<i class="icon-large icon-minus-sign"></i>',
        '#attributes' => array('title' => t('Remove field'),
			       'class' => array('islandora-solr-search-remove')),
        '#name' => 'remove-field-' . $i,
        '#ajax' => array(
			 'callback' => '_islandora_dss_solr_advanced_search_terms',
			 'wrapper' => 'islandora-solr-advanced-terms',
			 'method' => 'replace',
			 'effect' => 'fade',
			 'progress' => array('type' => 'none'),
			 ),
	//'#suffix' => '<button type="islandora-solr-search-remove"><i class="icon-large icon-minus-sign"></i></button>'
      );

      if ((variable_get('islandora_solr_search_boolean', 'user') == 'user') && ((count($values['terms']) -1) != $i)) {

	/*
        $term['boolean'] = array(
          '#type' => 'select',
          '#prefix' => '<div class="islandora-solr-advanced-boolean">',
          '#suffix' => '</div>',
          '#default_value' => isset($value['boolean']) ? $value['boolean'] : 'AND',
          '#options' => array(
            'AND' => 'AND',
            'OR' => 'OR',
            'NOT' => 'NOT'),
	  '#attributes' => array('class' => array('islandora-solr-search-boolean'))
        );
	*/
        $term['boolean'] = array(
          '#type' => 'radios',
          '#prefix' => '<div class="islandora-solr-advanced-boolean">',
          '#suffix' => '</div>',
          '#default_value' => isset($value['boolean']) ? $value['boolean'] : 'AND',
          '#options' => array(
            'AND' => 'And',
            'OR' => 'Or',
            'NOT' => 'Not'),
	  '#attributes' => array('class' => array('islandora-solr-search-boolean'))
        );
      }
    }

    $terms[] = $term;
  }

  //dpm($terms);

  // For terms...
  if(count($values['terms']) < 5) {

    $terms[] = array('add' => array(
				    '#type' => 'button',
				    '#value' => '<i class="icon-large icon-plus-sign"></i>',
				    '#attributes' => array('title' => t('Add a field'),
							   'class' => array('islandora-solr-search-add')),
				    '#name' => 'add-field-' . $i,
				    '#ajax' => array(
						     'callback' => '_islandora_dss_solr_advanced_search_terms',
						     'wrapper' => 'islandora-solr-advanced-terms',
						     'method' => 'replace',
						     'effect' => 'fade',
						     'progress' => array('type' => 'none'),
						     ),
				    //'#suffix' => '<button type="islandora-solr-search-add"><i class="icon-large icon-plus-sign"></i></button>',
				    ));
  }

  // set form
  $form = array();
  // add terms
  $form['terms'] = $terms;

  // add controls
  $form['controls'] = array('#type' => 'markup',
			    '#prefix' => '<div class="islandora-solr-advanced-controls">',
			    '#suffix' => '</div>');

  $form['controls']['submit'] = array('#type' => 'submit',
				      '#value' => t('Search')
				      );

  return $form;
  }

  /**
   * Implements hook_islandora_solr_query_blocks().
   *
   * @see islandora_solr_islandora_solr_query_blocks()
   *
   */
function islandora_dss_solr_islandora_solr_query_blocks() {

  return array(
	       'dss-advanced' => array('name' => t('DSS Islandora Advanced Search'),
				       'module' => 'islandora_dss_solr',
				       'file' => 'includes/blocks.inc',
				       'class' => NULL,
				       'function' => NULL,
				       'form' => 'islandora_dss_solr_advanced_search_form',
				       ),
	       );
}
