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
 * AJAX callback for advanced search form
 * This should be extended for the rescoping of a search based upon collection-specific attributes
 *
 * @param type $form
 * @param type $form_state
 * @return type
 *
 * @see islandora_solr_advanced_search_form()
 */
function _islandora_dss_solr_advanced_search_terms_rescope($form, &$form_state) {

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

/*
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
*/

$ISLANDORA_DSS_FIELDS = array('foxml.all.text' => 'Full Text',
			      'dc.title' => 'Title',
			      'dc.contributor' => 'Author',
			      );

function islandora_dss_fields_map($collection) {

  $ISLANDORA_DSS_FIELDS_MAP = array('eastasia' => array(
							'foxml.all.text' => 'Full Text',
							'dc.title' => 'Title.English',
							'eastasia.Title.Japanese' => 'Title.Japanese', // Resolve with re-indexing (DSSSM-614 )
							'eastasia.Title.Chinese' => 'Title.Chinese', // DSSSM-614
							'eastasia.Title.Korean' => 'Title.Korean', // DSSSM-614
							"eastasia.Contributors.Digital" => 'Contributor',
							"eastasia.Contributor.Donor" => 'Contributor.Donor',
							"eastasia.Coverage.Location" => 'Coverage.Location',
							"eastasia.Coverage.Location.Country" => 'Coverage.Location.Country',
							"eastasia.Creator.Company" => 'Creator.Company',
							"eastasia.Creator.Maker" => 'Creator.Maker',
							"eastasia.Date.Artifact.Lower" => 'Date.Artifact.Lower',
							"eastasia.Date.Artifact.Upper" => 'Date.Artifact.Upper',
							"eastasia.Date.Image.Lower" => 'Date.Image.Lower',
							"eastasia.Date.Image.Upper" => 'Date.Image.Upper',
							"eastasia.Date.Original" => 'Date.Original',
							'mdl_prints.description' => 'Description.Caption.English',
							'mdl_prints.description' => 'Description.Caption.Japanese',
							'mdl_prints.description' => 'Description.Citation', // (DSSSM-614 ?)
							'geology_slides.description.critical' => 'Description.Critical',
							"eastasia.Description.Ethnicity" => 'Description.Ethnicity',
							"eastasia.Description.Indicia" => 'Description.Indicia',
							'mdl_prints.format.extent' => 'Format.Extent',
							"eastasia.Format.Medium" => 'Format.Medium',
							"cdm.Relation.IsPartOf" => 'Relation.IsPartOf',
							"eastasia.Subject.OCM" => 'Subject.OCM',
							),
				    /*
				    'academic' => array(
							'foxml.all.text' => 'Full Text',
							'dc.description.abstract' => 'Abstract',
							'dc.identifier.issn' => 'Series',
							'dc.contributor.author' => 'Author',
							'dc.title' => 'Title',
							'dc.subject' => 'Keyword',
							'dc.language.iso' => 'Language (ISO)',
							'dc.type' => 'MIME-Type',
							'dc.' => 'Sponsor',
							'dc.identifier.isbn' => 'Identifier',
							),
				    */
				    //'administration' => array(),
				    'newspaper' => array(
							 'foxml.all.text' => 'Full Text',
							 'dc.date' => 'Publication Date'
							 ),
				    'cap' => array(
						   'foxml.all.text' => 'Full Text',
						   'dc.title' => 'Title',
						   'dc.description' => 'Description',
						   'dc.type' => 'Medium',
						   'mdl_prints.date.original' => 'Publication Date',
						   'geology_slides_esi.subject' => 'Subject',
						   ),
				    'mdl-prints' => array(
							  'foxml.all.text' => 'Full Text',
							  'dc.title' => 'title',
							  'mdl_prints.creator' => 'creator',
							  'mdl_prints.date.original' => 'date.original',
							  'mdl_prints.description' => 'description',
							  'mdl_prints.description.condition' => 'description.condition',
							  'mdl_prints.description.note' => 'description.note',
							  'mdl_prints.description.provenance' => 'description.provenance',
							  'mdl_prints.description.series' => 'description.series',
							  'mdl_prints.format.digital' => 'format.digital',
							  'mdl_prints.format.extent' => 'format.extent',
							  'mdl_prints.format.medium' => 'format.medium',
							  'mdl_prints.identifier.itemnumber' => 'identifier.item.number',
							  'mdl_prints.publisher.digital' => 'publisher.digital',
							  'mdl_prints.publisher.original' => 'publisher.original',
							  'cdm.Relation.IsPartOf' => 'relation.IsPartOf',
							  'mdl_prints.rights.digital' => 'rights.digital',
							  'mdl_prints.publisher.digital' => 'source',
							  'mdl_prints.subject.lcsh' => 'subject.lcsh',
							  ),
				    'geology-slides' => array(
							      'foxml.all.text' => 'Full Text',
							      'dc.title' => 'Title',
							      'geology_slides_esi.coverage.location' => 'Coverage',
							      'geology_slides_esi.description' => 'Description',
							      'geology_slides_esi.date.original' => 'Publication Date',
							      'geology_slides_esi.relation.seealso.book' => 'Related Book',
							      'geology_slides_esi.relation.seealso.image' => 'Related Image',
							      'geology_slides_esi.subject' => 'Subject',
							      'geology_slides_esi.description.vantagepoint' => 'Vantage Point',
							      ),
				    'mckelvy' => array(
						       'foxml.all.text' => 'Full Text',
						       'dc.title' => 'Title',
						       'mckelvy.creator.maker' => 'Creator',
						       'geology_slides_esi.description' => 'Description',
						       'mckelvy.description.size' => 'Dimensions',
						       'mckelvy.format.medium' => 'Medium',
						       'mckelvy.description.note' => 'Note',
						       'mckelvy.date.original.search' => 'Publication Date',
						       'geology_slides_esi.subject' => 'Subject',
						       ),
				    'war-casualties' => array(
							      'foxml.all.text' => 'Full Text',
							      'dc.title' => 'Name',
							      'war_casualties.description.cause.death' => 'Cause of Death',
							      'war_casualties.date.birth.display' => 'Date of Birth',
							      'war_casualties.date.death.display' => 'Date of Death',
							      'war_casualties.description.class' => 'Graduating Class',
							      'war_casualties.description.military.branch' => 'Military Branch',
							      'war_casualties.description.honors' => 'Military Honors',
							      'war_casualties.description.military.rank' => 'Military Rank',
							      'war_casualties.contributor.military.unit' => 'Military Unit',
							      'war_casualties.coverage.place.birth' => 'Place of Birth',
							      'war_casualties.coverage.place.death' => 'Place of Death',
							      ),
				    'magazine' => array('foxml.all.text' => 'Full Text',
							'MODS.mods.relatedItem.date.w3cdtf_dts' => 'Date',
							),
				    'shakespeare' => array('foxml.all.text' => 'Full Text',
							   'MODS.mods.originInfo.dateIssued.w3cdtf_dt' => 'Date',
							   )
				    );

  //$ISLANDORA_DSS_FIELDS_MAP['administration'] = array_merge($ISLANDORA_DSS_FIELDS_MAP['academic'], $ISLANDORA_DSS_FIELDS_MAP['administration']);
  
  // Ensure that the merge isn't performed for certain collections
  
  // Thom: It seems none of the collections should have the merge performed
  
  /*if(!in_array($collection, array('eastasia', 'mdl-prints', 'newspaper', 'cap', 'geology-slides', 'mckelvy', 'war-casualties',))) {

    global $ISLANDORA_DSS_FIELDS;
    $fields = array_merge($ISLANDORA_DSS_FIELDS_MAP[$collection], $ISLANDORA_DSS_FIELDS);
  }*/

  //return $fields;
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
 * Deprecated
 * @todo Remove
 *
 */
function islandora_dss_solr_get_fields_for_collection($collection='') {

  
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

  // Refactor for the administrative interface
  $ISLANDORA_DSS_SOLR_DATE_FIELDS = array(
					  'dc.date',
					  "eastasia.Date.Artifact.Lower",
					  "eastasia.Date.Artifact.Upper",
					  "eastasia.Date.Image.Lower",
					  "eastasia.Date.Image.Upper",
					  "eastasia.Date.Original",
					  'mdl_prints.date.original',
					  'geology_slides_esi.date.original',
					  'mckelvy.date.original.search',
					  'war_casualties.date.birth.display',
					  'war_casualties.date.death.display',

					  'MODS.mods.relatedItem.date.w3cdtf_dts',
					  'MODS.mods.originInfo.dateIssued.w3cdtf_dt'
					  );

  drupal_load('module', 'search');
  $search_form = drupal_get_form('search_block_form');

  // include common.inc
  module_load_include('inc', 'islandora_solr', 'includes/common');

  // check form states
  // 1. form update using ajax
  // 2. populate with current query on search results page
  // 3. anywhere else: empty form

  // 1. form update using ajax
  if (isset($form_state['triggering_element']) and
      ($form_state['triggering_element']['#name'] != 'scoping')) {

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

  } elseif (islandora_solr_results_page($_islandora_solr_queryclass) == TRUE and
	    !isset($_islandora_solr_queryclass->internalSolrParams['type'])) {

    // 2. populate with current query on search results page

    // get current query
    $query = $_islandora_solr_queryclass->solrQuery;
    // set value variable
    $values['terms'] = array();

    /**
     * Ensure that global searches are not parsed
     *
     */
    if($query == '*:*') {

      $query = '';
    }

    // explode on space
    $query_explode = explode(' ', $query);

    /**
     * Handle the parsing of the query for the work-around
     * This resolves DSS-210
     *
     */

    /**
     * @todo Refactor
     *
     */

    //if(preg_match('/cdm.Relation.IsPartOf:"(.+)"/', $collection, $m)) {
    //if(array_key_exists('foxml.all.text', $query_explode)) {
    //if(preg_match('/foxml\.all\.text/', $query)) {
    /*
    if(false) {

      // Url parameters.
      $params = $_GET;
      $collection = $params['f']['0'];
      $collection = array_pop(explode(':', $collection));
      preg_match('/"(.+?)"/', $collection, $m);
      $collection = $m[1];

      $ISLANDORA_DSS_SOLR_RELATION_MAP = array('East Asia Image Collection'=> 'eastasia',
					       'Lafayette Newspaper Collection'=> 'newspaper',
					       //'Academic Publications' => 'academic',
					       'Historical Photograph Collection' => 'cap',
					       'Marquis de Lafayette Prints Collection' => 'mdl-prints',
					       'Geology Slide Collection' => 'geology-slides',
					       //'Administration Archives' => 'administration',
					       'McKelvy House Photograph Collection' => 'mckelvy',
					       'Lafayette World War II Casualties' => 'war-casualties',
					       );

      $collection_fields = array_keys(islandora_dss_fields_map( $ISLANDORA_DSS_SOLR_RELATION_MAP[$collection] ));

      foreach($collection_fields as $collection_field) {

	//eastasia.Subject.OCM:("taiwan" OR "Taiwan") OR 
	$query = preg_replace("/$collection_field\:\(.+?\) OR /", '', $query);

	if(!preg_match('/Date\./', $collection_field)) {

	  $query_array[] = array(
				 //'search' => "$collection_field:($search or )",
				 'search' => "$collection_field:$search",
				 'boolean' => 'OR'
				 );
	}
      }

    }
    */

    /**
     * Remove the query work-arounds for case-insensitive searches
     * @todo Resolve by reindexing Solr
     *
     */

    // For boolean-based overrides at the field-level
    $query = preg_replace("/\:\(\"(.+?)\" OR \".+?\" OR \".+?\"\)/", ':("\1")', $query);
    // For queries without quotations
    $query = preg_replace("/\:\((.+?) OR .+? OR .+?\)/", ':(\1)', $query);
    // This should be deprecated
    $query = preg_replace("/\:\(\"(.+?)\" OR \".+?\"\)/", ':("\1")', $query);


    //$query = preg_replace("/\:\((.+?) OR .+?\)/", ':(\1)', $query);

    // For range overrides at the field-level
    //$query = preg_replace("/\:\[(.+?) TO .+?\]/", ':(\1)', $query);

    // For range overrides at the field-level
    // Need to break more complex queries
    if(preg_match('/\:\[(.+?) TO (.+?)\]/', $query, $range_match)) {

      $query = preg_replace("/\:\[(.+?) TO .+?\]/", ':(\1)', $query);
    }

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
        $values['terms'][$i]['field-wrapper']['field'] = $value_split[0];

        // second part of the split is the query value (or first part of it)
        $value_split[1] = str_replace(array('(', ')'), '', $value_split[1]);

	/**
	 * Handling for datestamps
	 *
	 */
	if(in_array($value_split[0], $ISLANDORA_DSS_SOLR_DATE_FIELDS)) {

	  if(isset($range_match) and count($range_match) > 2) {

	    $date_u = strtotime($value_split[1] . ' UTC');
	    $date_v = strtotime($range_match[2] . ' UTC');

	    // Refactor using DateInterval and DateTime Classes (?)
	    // (Might consume more resources)
	    // Year: 31492799
	    // Month: 2635199
	    // Day: 43199
	    $date_diff = $date_v - $date_u;
	    if($date_diff >= 30000000) {

	      $values['terms'][$i]['field-wrapper']['search'] = gmdate('Y', $date_u);
	    } elseif($date_diff >= 2000000) {

	      $values['terms'][$i]['field-wrapper']['search'] = gmdate('Y-m', $date_u);
	    } else {

	      $values['terms'][$i]['field-wrapper']['search'] = gmdate('Y-m-d', $date_u);
	    }
	  }
	} else {

	  /**
	   * Handling for specially formatted query strings
	   * Resolves DSS-242
	   *
	   */
	  $query_segment = $value_split[1];
	  // Remove asterisks
	  $query_segment = preg_replace('/\*(.+?)\*/', '$1', $query_segment);

	  // Remove escaped whitespace
	  $query_segment = preg_replace('/\\ /', ' ', $query_segment);

	  // add search string
	  $values['terms'][$i]['field-wrapper']['search'] = $query_segment;
	}

	/**
	 * Remove quotes
	 * @todo Refactor
	 */
	if(array_key_exists('search', $values['terms'][$i]['field-wrapper'])) {

	  $values['terms'][$i]['field-wrapper']['search'] = preg_replace('/"(.+?)"/', '$1', $values['terms'][$i]['field-wrapper']['search']);
	}
      }
      // if the string does not include a colon or AND/OR/NOT, then it is a
      // part of the query value
      elseif (!preg_match('/(AND|OR|NOT)/', $value, $matches)) {

        // trim brackets
        $value = str_replace(array('(', ')'), '', $value);

        if (isset($values['terms'][$i]['field-wrapper']['search'])) {
          // append to search string
          $values['terms'][$i]['field-wrapper']['search'] .= ' ' . $value;
        }
        else {
          // search field is not set, so create new search value
          $values['terms'][$i]['field-wrapper']['search'] = $value;
        }

	/**
	 * Remove quotes
	 * @todo Refactor
	 */
	if(array_key_exists('search', $values['terms'][$i]['field-wrapper'])) {

	  $values['terms'][$i]['field-wrapper']['search'] = preg_replace('/"(.+?)"/', '$1', $values['terms'][$i]['field-wrapper']['search']);
	}
      }
      // if it matches AND/OR/NOT, then we have the boolean operator
      else {

        // set boolean operator
        $values['terms'][$i]['field-wrapper']['boolean'] = $value;

	// increment to next field
	$i++;
      }

      /**
       * Handling for specially formatted query strings
       * Resolves DSS-242
       *
       */

      if(count($values['terms']) > $i and array_key_exists('search', $values['terms'][$i]['field-wrapper'])) {

	$term_query = $values['terms'][$i]['field-wrapper']['search'];

	// Remove wildcards
	$term_query = preg_replace('/\*(.+?)\*/', '$1', $term_query);
	// Remove escaped whitespace
	//$term_query = preg_replace('/\\\ /', ' ', $term_query);
	$term_query = str_replace('\ ', ' ', $term_query);
	// Remove escaped brackets
	//$term_query = preg_replace('/\\\\\[/', '[', $term_query);
	//$term_query = preg_replace('/\\\\\]/', ']', $term_query);
	$term_query = str_replace('\[', '[', $term_query);
	$term_query = str_replace('\]', ']', $term_query);
	

	// add search string
	$values['terms'][$i]['field-wrapper']['search'] = $term_query;
      }
    }
  } elseif(preg_match('/search\/node\/(.+)/', current_path(), $apachesolr_query_match)) { // Extending for integration with apachesolr

    // 2. populate with current query on search results page

    // get current query
    $query = $apachesolr_query_match[1];
    // set value variable
    $values['terms'] = array();

    /**
     * Ensure that global searches are not parsed
     *
     */
    if($query == '*:*') {

      $query = '';
    }

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
        $values['terms'][$i]['field-wrapper']['field'] = $value_split[0];

        // second part of the split is the query value (or first part of it)
        $value_split[1] = str_replace(array('(', ')'), '', $value_split[1]);

	/**
	 * Handling for specially formatted query strings
	 * Resolves DSS-242
	 *
	 */
	$query_segment = $value_split[1];
	// add search string
	$values['terms'][$i]['field-wrapper']['search'] = $query_segment;
      }
      // if the string does not include a colon or AND/OR/NOT, then it is a
      // part of the query value
      elseif (!preg_match('/(AND|OR|NOT)/', $value, $matches)) {
        // trim brackets
        $value = str_replace(array('(', ')'), '', $value);

        if (isset($values['terms'][$i]['field-wrapper']['search'])) {
          // append to search string
          $values['terms'][$i]['field-wrapper']['search'] .= ' ' . $value;
        }
        else {
          // search field is not set, so create new search value
          $values['terms'][$i]['field-wrapper']['search'] = $value;
        }
      }
      // if it matches AND/OR/NOT, then we have the boolean operator
      else {
        // set boolean operator
        $values['terms'][$i]['field-wrapper']['boolean'] = $value;

	// increment to next field
	$i++;
      }

      /**
       * Handling for specially formatted query strings
       * Resolves DSS-242
       *
       */

      if(count($values['terms']) > $i and array_key_exists('search', $values['terms'][$i]['field-wrapper'])) {

	$term_query = $values['terms'][$i]['field-wrapper']['search'];

	// add search string
	$values['terms'][$i]['field-wrapper']['search'] = $term_query;
      }
    }

  } else { // 3. anywhere else: empty form

    //Need at least one term to draw the search box.
    $values = array('terms' => array(''));
  }

  $terms = array(
    '#type' => 'markup',
    '#prefix' => '<div id="islandora-solr-advanced-terms">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  /**
   * Ensure that additional fields are not added when the collection field is modified
   *
   */
  if(array_key_exists('triggering_element', $form_state) and $form_state['triggering_element']['#name'] == 'collection') {

    $values['terms'] = array_slice($values['terms'], 0, -1);
  }

  // Retrieve and store the current path
  $current_path = current_path();

  $cdm_relation_collection_map = array(
				       'Japanese Imperial House Postcard Album'  => 'eastasia',
				       'T.W. Ingersoll Co. Stereoviews of the Siege of Port Arthur'  => 'eastasia',
				       'Imperial Postcard Collection'  => 'eastasia',
				       'Tsubokura Russo-Japanese War Postcard Album'  => 'eastasia',
				       'Sino-Japanese War Postcard Album 01'  => 'eastasia',
				       'Sino-Japanese War Postcard Album 02'  => 'eastasia',
				       'Lin Chia-Feng Family Postcard Collection'  => 'eastasia',
				       'Japanese History Study Cards'  => 'eastasia',
				       'Pacific War Postcard Collection'  => 'eastasia',
				       'Michael Lewis Taiwan Postcard Collection'  => 'eastasia',
				       'Gerald & Rella Warner Taiwan Postcard Collection'  => 'eastasia',
				       'Gerald & Rella Warner Dutch East Indies Negative Collection'  => 'eastasia',
				       'Japanese Imperial House Postcard Album'  => 'eastasia',
				       'Gerald & Rella Warner Manchuria Negative Collection'  => 'eastasia',
				       'Gerald & Rella Warner Taiwan Negative Collection'  => 'eastasia',
				       'Gerald & Rella Warner Japan Slide Collection'  => 'eastasia',
				       'Gerald & Rella Warner Souvenirs of Beijing and Tokyo'  => 'eastasia',
				       'Woodsworth Taiwan Image Collection'  => 'eastasia',
				       'Scenic Taiwan'  => 'eastasia',
				       'Taiwan Photographic Monthly'  => 'eastasia',

				       'East Asia Image Collection' => 'eastasia',

				       'Geology Department Slide Collection' => 'geology-slides',
				       'Historical Photograph Collection' => 'cap',
				       'Lafayette Newspaper Collection' => 'newspaper',
				       'Marquis de Lafayette Prints Collection' => 'mdl-prints',
				       'McKelvy House Photograph Collection' => 'mckelvy',
				       'Lafayette World War II Casualties' => 'war-casualties',

				       'Lafayette Magazine Collection' => 'magazine',
				       'Shakespeare Bulletin Archive' => 'shakespeare'
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

    /**
     * For resolving issues related to case sensitivity in searches
     * Resolves DSS and DSSSM-709
     *
     */
    if(isset($value['field-wrapper']) and array_key_exists('field', $value['field-wrapper'])) {

      $value['field-wrapper']['field'] = str_replace('c_', '', $value['field-wrapper']['field']);
    }

    $term['field-wrapper']['field'] = array('#title' => t(''),
					    '#type' => 'select',
					    '#default_value' => ((isset($value['field-wrapper']) and array_key_exists('field', $value['field-wrapper'])) ? $value['field-wrapper']['field'] : 'Full Text'),
					    '#attributes' => array('class' => array('islandora-solr-search-field')));

    if(isset($form_state['triggering_element']) and $form_state['triggering_element']['#name'] == 'scoping') {

      /*
      switch($form_state['triggering_element']['#value']) {

      case 'COLL':
	//$term['field-wrapper']['field']['#options'] = islandora_dss_solr_get_fields($form_state['values']['collection'], 'search_fields');
	$term['field-wrapper']['field']['#options'] = islandora_dss_fields_map($form_state['values']['collection']);
	break;

      case 'REPO':
	$term['field-wrapper']['field']['#options'] = islandora_solr_get_fields('search_fields');
	break;

	case 'SITE':
      default:
	$term['field-wrapper']['field']['#options'] = array('keywords' => 'DSS Pages');
        break;
      }
      */

      if($form_state['triggering_element']['#value'] == 'COLL') {

	if($form_state['values']['collection'] == 'global') {

	  $term['field-wrapper']['field']['#options'] = islandora_solr_get_fields('search_fields');
	} else {

	  //$term['field-wrapper']['field']['#options'] = islandora_dss_solr_get_fields($form_state['values']['collection'], 'search_fields');
	  $term['field-wrapper']['field']['#options'] = islandora_dss_fields_map($form_state['values']['collection']);
	}
      } else {

	$term['field-wrapper']['field']['#options'] = array('keywords' => 'DSS Pages');
	//$form_state['values']['collection'] = 'global';
	//$default_collection_value = 'global';
      }

    } elseif(isset($form_state['triggering_element']) and
	     ($form_state['triggering_element']['#name'] == 'collection' or ($form_state['triggering_element']['#type'] == 'button' and $form_state['triggering_element']['#value'] == '<i class="icon-large"></i>'))) {

      if($form_state['values']['scoping'] == 'SITE') {

	$term['field-wrapper']['field']['#options'] = array('keywords' => 'DSS Pages');
      } elseif($form_state['values']['collection'] == 'global') {

	$term['field-wrapper']['field']['#options'] = islandora_solr_get_fields('search_fields');
      } else {

	$term['field-wrapper']['field']['#options'] = islandora_dss_fields_map($form_state['values']['collection']);
      }
    } else {

      /**
       * Seek to populate the individual field options based upon the collection being browsed
       * Resolves DSS-226
       *
       */
      if(array_key_exists('f', $_GET)) {

	$facets = $_GET['f'];
	foreach($facets as $facet) {

	  if(preg_match('/cdm\.Relation\.IsPartOf\:"(.+?)"/', $facet, $collection_m)) {

	    if(array_key_exists($collection_m[1], $cdm_relation_collection_map)) {

	      $default_collection_value = $cdm_relation_collection_map[$collection_m[1]];

	      /**
	       * If this is an active search, then update the term field with respect to the collection being browsed
	       * This resolves DSSSM-621
	       *
	       */
	      $term['field-wrapper']['field']['#options'] = islandora_dss_fields_map($default_collection_value);
	    }
	  }
	}
      }

      // If the options weren't populated from the Solr facets...
      if(!array_key_exists('#options', $term['field-wrapper']['field'])) {

	// Refactor
	if(preg_match('/search\/node/', $current_path)) {
	  
	  $term['field-wrapper']['field']['#options'] = array('keywords' => 'DSS Pages');
	} else {

	  $term['field-wrapper']['field']['#options'] = islandora_solr_get_fields('search_fields');
	}
      }
    }

    // Initialize the form field for a specific search term
    $term['field-wrapper']['search'] = array('#title' => t(''),
					     '#type' => 'textfield',
					     '#size' => 80,
					     '#default_value' => isset($value['field-wrapper']) ? $value['field-wrapper']['search'] : '',
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
			   );
    }
    */

    if (count($values['terms']) > 1) {
      
      $term['field-wrapper']['remove'] = array(

        '#type' => 'button',
        '#field' => $i,
	'#value' => '<i class="icon-large"></i>',
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

	/**
	 * Work-around
	 * @todo Refactor for DSSSM-774
	 *
	 */
	if(array_key_exists('boolean', $value)) {

	  $term_boolean_default_value = isset($value['boolean']) ? $value['boolean'] : 'AND';
	} else {
	  
	  $term_boolean_default_value = isset($value['field-wrapper']['boolean']) ? $value['field-wrapper']['boolean'] : 'AND';
	}

	$term['boolean'] = array(
				 '#type' => 'radios',
				 '#prefix' => '<div class="islandora-solr-advanced-boolean">',
				 '#suffix' => '</div>',
				 '#default_value' => $term_boolean_default_value,
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

  /**
   * If there are less than 6 fields, permit the user to add a field
   *
   */
  if(count($values['terms']) < 5) {

    $classes = array('islandora-solr-search-add');
    if(count($values['terms']) == 1) {

      $classes[] = 'raised';
    }

    $terms[] = array('add' => array(
				    '#type' => 'button',
				    '#value' => '<i class="icon-large"></i>',
				    '#attributes' => array('title' => t('Add a field'),
							   'class' => $classes),
				    '#name' => 'add-field-' . $i,
				    '#ajax' => array(
						     'callback' => '_islandora_dss_solr_advanced_search_terms',
						     'wrapper' => 'islandora-solr-advanced-terms',
						     'method' => 'replace',
						     'effect' => 'fade',
						     'progress' => array('type' => 'none'),
						     ),
				    ));
  }

  // set form
  $form = array();

  if(isset($form_state['triggering_element'])) {

    $scoping_options = $form_state['complete form']['scoping']['#options'];

    // For capturing the path passed via AJAX for form field population
    $form['path'] = array('#type' => 'hidden', '#value' => $form_state['values']['path']);
  } else {

    $scoping_options = array('SITE' => 'Search the DSS Site');
    $scoping_options['COLL'] = 'Search our collections:';

    // For capturing the path passed via AJAX for form field population
    $form['path'] = array('#type' => 'hidden', '#value' => $current_path);
  }

  if(preg_match('/search\/node/', current_path())) {

    $scoping_default_value = 'SITE';
  } else {

    $scoping_default_value = 'COLL';
  }

  // Set the scoping controls
  $form['scoping'] = array('#type' => 'radios',
			   //'#prefix' => '<div class="islandora-solr-advanced-scoping">',
			   '#prefix' => '<div id="islandora-solr-advanced-scoping">',
			   '#suffix' => '</div>',
			   '#default_value' => $scoping_default_value,
			   '#options' => $scoping_options,
			   '#attributes' => array('class' => array('islandora-solr-scoping-button')),
			   '#ajax' => array(
					    'wrapper' => 'islandora-solr-advanced-terms',
					    'callback' => '_islandora_dss_solr_advanced_search_terms_rescope',
					    'method' => 'replace',
					    'effect' => 'fade',
					    'progress' => array('type' => 'none'),
					    ),
			   );

  /**
   * Retrieve this from the path being browsed
   * This resolves DSSSM-618
   *
   */
  $default_collection_value = 'global';
  $collection_node_map = array(
			       'node/26' => 'eastasia',
			       'node/21' => 'newspaper',
			       //'academic' => 'Academic Publications',
			       'node/20' => 'cap',
			       'node/27' => 'mdl-prints',
			       'node/19' => 'geology-slides',
			       //'administration' => 'Administration Archives',
			       'node/42' => 'mckelvy',
			       'node/43' => 'war-casualties',

			       // This resolves DSS-420
			       'node/52' => 'magazine',

			       '/' => 'shakespeare'
			       );

  $alias_collection_map = array(
				'eastasia'  => 'eastasia',
				'geology' => 'geology-slides',
				'historicalphotos' => 'cap',
				'newspaper' => 'newspaper',
				'lafayetteprints' => 'mdl-prints',
				'mckelvy' => 'mckelvy',
				'war' => 'war-casualties',

				// This resolves DSS-420
				'magazine' => 'magazine',

				'shakespeare' => 'shakespeare'
				);

  if(array_key_exists($current_path, $collection_node_map)) {

    $default_collection_value = $collection_node_map[$current_path];

    /**
     * If this is a new search, then update the term field with respect to the collection being browsed
     * This resolves DSSSM-621
     *
     */
    if(!array_key_exists('field-wrapper', $terms[1]) and $terms[0]['field-wrapper']['search']['#default_value'] == '') {

      $terms[0]['field-wrapper']['field']['#options'] = islandora_dss_fields_map($default_collection_value);
    }
  } elseif(array_key_exists('f', $_GET)) {

    $facets = $_GET['f'];
    foreach($facets as $facet) {

      if(preg_match('/cdm\.Relation\.IsPartOf\:"(.+?)"/', $facet, $collection_m)) {

	if(array_key_exists($collection_m[1], $cdm_relation_collection_map)) {

	  $default_collection_value = $cdm_relation_collection_map[$collection_m[1]];

	  /**
	   * If this is a new search, then update the term field with respect to the collection being browsed
	   * This resolves DSSSM-621
	   *
	   */
	  if(!array_key_exists('field-wrapper', $terms[1]) and $terms[0]['field-wrapper']['search']['#default_value'] == '') {

	    $terms[0]['field-wrapper']['field']['#options'] = islandora_dss_fields_map($default_collection_value);
	  }
	}
      }
    }
  } elseif(preg_match('/collections\/(.+?)\//', drupal_get_path_alias($current_path), $alias_m)) {

    /**
     * This permits searches at the Object-level
     * Required is that the proper path alias has been generated within Drupal
     * This resolves DSSSM-714
     *
     */
    if(array_key_exists($alias_m[1], $alias_collection_map)) {

      $default_collection_value = $alias_collection_map[$alias_m[1]];

      /**
       * If this is a new search, then update the term field with respect to the collection being browsed
       * This resolves DSSSM-621
       *
       */
      if(!array_key_exists('field-wrapper', $terms[1]) and $terms[0]['field-wrapper']['search']['#default_value'] == '') {
	
	$terms[0]['field-wrapper']['field']['#options'] = islandora_dss_fields_map($default_collection_value);
      }      
    }
  }

  $form['collection'] = array(
			      //'#prefix' => '<span>Search: </span>',
			      '#title' => '',
			      '#type' => 'select',
			      '#default_value' => $default_collection_value,
			      '#options' => array(
						  'global' => 'All',
						  //'academic' => 'Academic Publications',
						  //'administration' => 'Administration Archives',
						  'eastasia' => 'East Asia Image Collection',
						  'geology-slides' => 'Geology Slide Collection',
						  'cap' => 'Historical Photograph Collection',
						  'war-casualties' => 'Lafayette College World War II Casualties',
						  'newspaper' => 'Lafayette Newspaper',
						  'mdl-prints' => 'Marquis de Lafayette Prints Collection',
						  'mckelvy' => 'McKelvy House',
						  'magazine' => 'Lafayette Magazine',
						  'shakespeare' => 'Shakespeare Bulletin Archive'
						  ),
			      '#ajax' => array(
					       'wrapper' => 'islandora-solr-advanced-terms',
					       'callback' => '_islandora_dss_solr_advanced_search_terms_rescope',
					       'method' => 'replace',
					       'effect' => 'fade',
					       'progress' => array('type' => 'none'),
					       'event' => 'change'
					       ),
			      //'#disabled' => $collection_disabled
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

  /**
   * This key must be present for the implementation of hook_form_alter() within the bootstrap theme
   * Resolves EDDC-77
   * @todo Refactor
   *
   */
  $form['actions']['#type'] = '';

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

  /**
   * For searches scoped to the site, simply redirect the query to the appropriate apachesolr callback
   *
   */
  if(array_key_exists('scoping', $form_state['values']) and $form_state['values']['scoping'] == 'SITE') {

    // Work-around
    /* @todo Refactor (once Islandora 7 has integrated islandora_solr_search with the Drupal Search API) */
    $query = '';
    foreach($form_state['values']['terms'] as $term) {

      if(array_key_exists('field-wrapper', $term)) {

	$query .= "{$term['field-wrapper']['search']} ";
	if(array_key_exists('boolean', $term)) {

	  $query .= "{$term['boolean']} ";
	}
      }
    }

    drupal_goto('search/node/' . $query);
  }

  // Refactor for the administrative interface
  $ISLANDORA_DSS_SOLR_DATE_FIELDS = array(
					  'dc.date',
					  "eastasia.Date.Artifact.Lower",
					  "eastasia.Date.Artifact.Upper",
					  "eastasia.Date.Image.Lower",
					  "eastasia.Date.Image.Upper",
					  "eastasia.Date.Original",
					  'mdl_prints.date.original',
					  'geology_slides_esi.date.original',
					  'mckelvy.date.original.search',
					  'war_casualties.date.birth.display',
					  'war_casualties.date.death.display',

					  'MODS.mods.relatedItem.date.w3cdtf_dts',
					  'MODS.mods.originInfo.dateIssued.w3cdtf_dt'
					  );

  // Collect query values
  $query_array = array();
  foreach ($form_state['values']['terms'] as $term) {

    if(array_key_exists('field-wrapper', $term)) {

      // set field
      $field = $term['field-wrapper']['field'];

      // set search value
      $search = trim($term['field-wrapper']['search']);

      //replace the slash so url doesn't break
      //$search = str_replace('/', '~slsh~', $search);

      /**
       * Handling for Lucene metacharacters
       * Resolving DSSSM-775
       * @todo Refactor
       *
       */
      $ISLANDORA_DSS_SOLR_LUCENE_METACHARS = array('/', ':', '?', '&');
      foreach($ISLANDORA_DSS_SOLR_LUCENE_METACHARS as $metachar) {

	$search = str_replace("$metachar", urlencode($metachar), $search);
      }

      // set boolean
      $boolean = (isset($term['boolean'])) ? $term['boolean'] : variable_get('islandora_solr_search_boolean', 'user');

      // add query
      if (!empty($search)) {

	/**
	 * Handling for date strings
	 * Resolves DSSSM-656
	 *
	 */
	if(in_array($field, $ISLANDORA_DSS_SOLR_DATE_FIELDS)) {

	  if(preg_match('/(\d{4})\-(\d{2})\-(\d{2})/', $search, $m)) {

	    // Refactor
	    $search_time_u = gmmktime(0, 0, 0, (int) $m[2], (int) $m[3], (int) $m[1]);
	    $search_time_v = gmmktime(11, 59, 59, (int) $m[2], (int) $m[3], (int) $m[1]);

	  } elseif(preg_match('/(\d{4})\-(\d{2})/', $search, $m)) {

	    // Refactor
	    $search_time_u = gmmktime(0, 0, 0, (int) $m[2], 1, (int) $m[1]);
	    $search_time_v = gmmktime(11, 59, 59, (int) $m[2], cal_days_in_month(CAL_GREGORIAN, (int) $m[2], (int) $m[1]), (int) $m[1]);

	  } elseif(preg_match('/(\d{4})/', $search, $m)) {

	    $search_time_u = gmmktime(0, 0, 0, 1, 1, (int) $m[1]);
	    $search_time_v = gmmktime(11, 59, 59, 12, 31, (int) $m[1]);
	  } else {

	    // No Objects should bear this time
	    $search_time_u = gmmktime(0, 0, 0, 1, 1, 0);
	    $search_time_v = gmmktime(11, 59, 59, 12, 31, 0);
	  }

	  // All dates must be passed as ranges
	  $search = str_replace('+00:00', '', gmdate('c', $search_time_u)) . 'Z TO ' . str_replace('+00:00', '', gmdate('c', $search_time_v)) . 'Z';

	  $query_array[] = array(
				 'search' => "$field:([$search])",
				 //'search' => "$field:$search",
				 'boolean' => $boolean
				 );
	} else {

	  // Ensure that terms are escaped with double quotations
	  if(!preg_match('/^"(.+?)"$/', $search)) {

	    $search = '"' . $search . '"';
	  }

	  $query_array[] = array(
				 'search' => "$field:($search)",
				 //'search' => "$field:$search",
				 'boolean' => $boolean
				 );
	}
      }
    }
  }

  /**
   * Scope the query based upon the collection selected
   * Resolves DSSSM-306
   *
   */

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
  /**
   * This ensures that, by default, only all titles are returned
   * (Otherwise, Solr can behave unpredictably due to the stress introduced by the query *:*
   *
   */
  if (empty($query)) {
    $query = 'dc.title:*';
  }

  /**
   * @todo Refactor
   *
   */
  $ISLANDORA_DSS_SOLR_RELATION_MAP = array('eastasia' => 'East Asia Image Collection',
					   'newspaper' => 'Lafayette Newspaper Collection',
					   'academic' => 'Academic Publications',
					   'cap' => 'Historical Photograph Collection',
					   'mdl-prints' => 'Marquis de Lafayette Prints Collection',
					   'geology-slides' => 'Geology Department Slide Collection',
					   'administration' => 'Administration Archives',
					   'mckelvy' => 'McKelvy House Photograph Collection',
					   'war-casualties' => 'Lafayette World War II Casualties',
					   'magazine' => 'Lafayette Magazine Collection',
					   'shakespeare' => 'Shakespeare Bulletin Archive'
					   );

  $params = array();
  //if(array_key_exists('scoping', $form_state['values']) and $form_state['values']['scoping'] == 'COLL') {
  if(array_key_exists('scoping', $form_state['values'])
     and $form_state['values']['scoping'] == 'COLL'
     and array_key_exists('collection', $form_state['values'])
     and $form_state['values']['collection'] != 'global') {

    //return search_box_form_submit();
    //$params = array('f[0]' => 'cdm.Relation.IsPartOf:"' . $ISLANDORA_DSS_SOLR_RELATION_MAP[$form_state['values']['collection']] . '"');
    $params['f[0]'] = 'cdm.Relation.IsPartOf:"' . $ISLANDORA_DSS_SOLR_RELATION_MAP[$form_state['values']['collection']] . '"';
  }

  // navigate to results page
  drupal_goto('islandora/search/' . $query, array('query' => $params));
}
