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

// _islandora_dss_solr_advanced_search_terms_rescope
function _islandora_dss_solr_advanced_search_terms_rescope($form, &$form_state) {

  //dpm($form_state['triggering_element']);
  //watchdog('islandora_dss_solr', 'the triggering form element is %element', array('%element' => dpm()), WATCHDOG_NOTICE, $link = NULL);

  /*
  foreach($form['terms'] as $key => $value) {

    if(is_int($key)) {

      
    }

  }
  */

  return $form['terms'];
}

function islandora_dss_solr_current_collection($path='') {

  if(!$path) {

    $path = current_path();
  }

  $alias = drupal_get_path_alias($path);

  if(preg_match('/(?:collections|projects)\/(.+)/', $alias, $m)) {

    // For sub-collections within the EAIC
    $collection = $m[1];
    if($collection == 'eastasia') {

      if(preg_match("/collections\/$collection\/(.+)/", $alias, $m)) {

	return $m[1];
      }
    }

    return $collection;
  } elseif(preg_match('/islandora\/object\/(.+)\/?/', $path, $m)) {

    if($m[1] != 'islandora:root') {

      return $m[1];
    }
  }

  return NULL;

  /*
  if(preg_match('/collections\/.+/', drupal_get_path_alias($path)) or
     preg_match('/projects\/.+/', drupal_get_path_alias($path)) or
     (preg_match('/islandora\/object\/.+/', $path) and !preg_match('/islandora\/object\/islandora\:root\/?/', $path) )) {
    
    $scoping_options['COLL'] = 'Search this collection';
  }
  */
}

/**

*/

$ISLANDORA_DSS_FIELDS = array(
			      array('dc.contributor' => 'Contributor'),
			      array('dc.creator' => 'Creator'),
			      array('dc.date' => 'Date'),
			      array('dc.description' => 'Description'),
			      array('dc.format' => 'Format'),
			      array('dc.language' => 'Language'),
			      array('dc.publisher' => 'Publisher'),
			      array('dc.rights' => 'Rights'),
			      array('dc.source' => 'Source'),
			      array('dc.subject' => 'Subject'),
			      array('dc.title' => 'Title'),
			      );

function islandora_dss_fields_map($collection) {

  $ISLANDORA_DSS_FIELDS_MAP = array('eastasia' => array(
							"eastasia.Subject.OCM" => 'Subject.OCM',
							"eastasia.Date.Image.Lower" => 'Date.Image.Lower',
							"eastasia.Date.Image.Upper" => 'Date.Image.Upper',
							"eastasia.Date.Artifact.Lower" => 'Date.Artifact.Lower',
							"eastasia.Date.Artifact.Upper" => 'Date.Artifact.Upper',
							"eastasia.Date.Original" => 'Date.Original',
							"eastasia.Date.Search" => 'Date.Search',
							"eastasia.Description.Ethnicity" => 'Description.Ethnicity',
							"eastasia.Coverage.Location.Country" => 'Coverage.Location.Country',
							"eastasia.Coverage.Location" => 'Coverage.Location',
							"eastasia.Format.Medium" => 'Format.Medium',
							"eastasia.Description.Indicia" => 'Description.Indicia',
							"eastasia.Creator.Maker" => 'Creator.Maker',
							"eastasia.Contributors.Digital" => 'Contributors.Digital',
							"eastasia.Creator.Company" => 'Creator.Company',
							"cdm.Relation.IsPartOf" => 'Relation.IsPartOf',
							),
				    'academic' => array(
							'' => 'Full Text',
							'' => 'Abstract',
							'' => 'Series',
							'' => 'Author',
							'' => 'Title',
							'' => 'Keyword',
							'' => 'Language (ISO)',
							'' => 'MIME-Type',
							'' => 'Sponsor',
							'' => 'Identifier',
							),
				    'administration' => array(),
				    'newspaper' => array(),
				    'cap' => array(
						   'cap.subject.LOC' => 'Subject',
						   'cap.creator.photographer' => 'Photographer',
						   'cap.format.medium' => 'Format',
						   'cap.format.size' => 'Physical Size',
						   'date.approximate' => 'Date',
						   'date.range' => 'Dates',
						   ),
				    'mdl-prints' => array(
							  'mdl_prints.description.note' => 'Note',
							  'mdl_prints.subject.lcsh' => 'Subject',
							  'mdl_prints.publisher.original' => 'Subject',
							  'mdl_prints.date.original' => 'Subject',
							  'mdl_prints.format.medium' => 'Subject',
							  'mdl_prints.format.extent' => 'Subject',
							  'mdl_prints.description.condition' => 'Note',
							'mdl_prints.description.provenance' => 'Note',
							'mdl_prints.description.series' => 'Note',
							'mdl_prints.identifier.itemnumber' => 'Note',
							'mdl_prints.publisher.digital' => 'Note',
							'mdl_prints.format.digital' => 'Note',
							'mdl_prints.rights.digital' => 'Note',
							'mdl_prints.relation.IsPartOf' => 'Note',
							),
				  'mckelvy' => array(
						     'mckelvy.description.note' => 'Note',
						     'mckelvy.creator.maker' => 'Note',
						     'mckelvy.format.medium' => 'Note',
						     'mckelvy.date.original.display' => 'Note',
						     'mckelvy.date.original.search' => 'Note',
						     'mckelvy.description.size' => 'Note',
						     ),
				  'war-casualties' => array(
							    'war_casualties.title.name' => 'Note',
							    'war_casualties.description.class' => 'Note',
							    'war_casualties.date.birth.display' => 'Note',
							    'war_casualties.date.birth.search' => 'Note',
							    'war_casualties.coverage.place.birth' => 'Note',
							    'war_casualties.description.military.branch' => 'Note',
							    'war_casualties.description.military.rank' => 'Note',
							    'war_casualties.contributor.military.unit' => 'Note',
							    'war_casualties.date.death.display' => 'Note',
							    'war_casualties.date.death.search' => 'Note',
							    'war_casualties.coverage.place.death' => 'Note',
							    'war_casualties.description.cause.death' => 'Note',
							    'war_casualties.description.honors' => 'Note',
							    ),
				    'presidents' => array(),
				    );

  $ISLANDORA_DSS_FIELDS_MAP['administration'] = array_merge($ISLANDORA_DSS_FIELDS_MAP['academic'], $ISLANDORA_DSS_FIELDS_MAP['administration']);

  return $ISLANDORA_DSS_FIELDS_MAP[$collection];
}



function islandora_dss_solr_fields_for_path($path='') {

  $collection = islandora_dss_solr_current_collection($path);

  if($collection) {

    return islandora_dss_fields_map($collection);
  }

  return array();
}

/**
 * Implementation integrating functionality for collection-level scoping of advanced searches
 *
 * @params string $field_type
 *   The type of field to query for. If not passed, the query returns all fields.
 * @params bool $filter
 *   If set to TRUE, it will filter the array agains user roles. If set to FALSE, it will return all results.
 * @params bool $simplify
 *   Whether to return the fields array as a simple term => label array.
 * @return array
 *   The query results as an array.
 *
 * @see islandora_solr_get_fields().
 *
 */

function islandora_dss_solr_get_fields($path='', $field_type = NULL, $filter = TRUE, $simplified = TRUE, $keys = FALSE) {

  $records = islandora_solr_get_fields($field_type, $filter, $simplified, $keys);
  $records = array_merge($records, islandora_dss_solr_fields_for_path($path));

  return $records;
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
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#name'] != 'scoping' ) {

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
					    //'#options' => islandora_dss_solr_get_fields('search_fields'),
					    '#attributes' => array('class' => array('islandora-solr-search-field')));

    if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#name'] == 'scoping' && $form_state['triggering_element']['#value'] == 'COLL' ) {

      $term['field-wrapper']['field']['#options'] = islandora_dss_solr_get_fields($form_state['values']['path'], 'search_fields');
    } else {

      $term['field-wrapper']['field']['#options'] = islandora_solr_get_fields('search_fields');
    }

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
        '#attributes' => array(
			       'title' => t('Remove field'),
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

  if(isset($form_state['triggering_element'])) {

    $scoping_options = $form_state['complete form']['scoping']['#options'];

    // For capturing the path passed via AJAX for form field population
    $form['path'] = array('#type' => 'hidden', '#value' => $form_state['values']['path']);
  } else {

    $scoping_options = array('SITE' => 'Search the DSS Site',
			     'REPO' => 'Search all collections');

    // Add collection-level scoping for individual collections
    $path = current_path();

    if(preg_match('/collections\/.+/', drupal_get_path_alias($path)) or
       preg_match('/projects\/.+/', drupal_get_path_alias($path)) or
       (preg_match('/islandora\/object\/.+/', $path) and !preg_match('/islandora\/object\/islandora\:root\/?/', $path) )) {
      
      $scoping_options['COLL'] = 'Search this collection';
    }

    // For capturing the path passed via AJAX for form field population
    $form['path'] = array('#type' => 'hidden', '#value' => $path);
  }

  // Set the scoping controls
  $form['scoping'] = array('#type' => 'radios',
			   //'#prefix' => '<div class="islandora-solr-advanced-scoping">',
			   '#prefix' => '<div id="islandora-solr-advanced-scoping">',
			   '#suffix' => '</div>',
			   '#default_value' => 'SITE',
			   '#options' => $scoping_options,
			   '#attributes' => array('class' => array('islandora-solr-scoping-boolean')),
			   '#ajax' => array(
					    'wrapper' => 'islandora-solr-advanced-terms',
					    'callback' => '_islandora_dss_solr_advanced_search_terms_rescope',
					    'method' => 'replace',
					    'effect' => 'fade',
					    'progress' => array('type' => 'none'),
					    ),
			   );

  /*
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
   */

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

function islandora_dss_solr_advanced_search_form_submit($form, &$form_state) {

  // Collect query values
  $query_array = array();
  foreach ($form_state['values']['terms'] as $term) {

    if(array_key_exists('field-wrapper', $term)) {

      // set field
      $field = $term['field-wrapper']['field'];

      // set search value
      $search = trim($term['field-wrapper']['search']);

      //replace the slash so url doesn't break
      $search = str_replace('/', '~slsh~', $search);

      // set boolean
      $boolean = (isset($term['boolean'])) ? $term['boolean'] : variable_get('islandora_solr_search_boolean', 'user');

      // add query
      if (!empty($search)) {

	$query_array[] = array(
			       'search' => "$field:($search)",
			       'boolean' => $boolean
			       );
      }
    }
  }

  // create query
  $query = '';
  $i = 0;
  foreach ($query_array as $term) {
    $query .= $term['search'];
    if (count($query_array) -1 != $i) {
      $query .= ' ' . $term['boolean'] . ' ';
    }
    $i++;
  }

  // check if query is empty
  if (empty($query)) {
    $query = '*:*';
  }

  // navigate to results page
  drupal_goto('islandora/search/' . $query);
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @see islandora_solr_advanced_search()
 *
 */

function islandora_dss_solr_form_islandora_dss_solr_advanced_search_form_alter(&$form, &$form_state) {

  /* dpm($form_state); */
}