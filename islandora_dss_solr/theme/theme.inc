<?php

  /**
   * @file Hook implementations for theming
   * @author griffinj@lafayette.edu
   *
   */

$ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP = array();
$ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP = array();

function islandora_dss_solr_dc_label_map($collection, $dc_field) {

  global $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP;

  if(array_key_exists($collection, $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP)) {

    if(array_key_exists($dc_field, $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP[$collection])) {

      return $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP[$collection][$dc_field];
    }
  }

  return NULL;
}

$ISLANDORA_DSS_SOLR_TOP_COLLECTION = '';

/**
 * Please see http://www.php.net/manual/en/function.ip2long.php#82397
 *
 * This assumes a subnet of 139.147.0.0/16 for Lafayette College servers
 * This assumes a subnet of 192.168.101.0/24 for the VPN
 */
function islandora_dss_solr_net_match($CIDR, $IP) {

  list($net, $mask) = explode('/', $CIDR);
  return ( ip2long ($IP) & ~((1 << (32 - $mask)) - 1) ) == ip2long ($net);
} 

/**
 * hook_process function for islandora_solr
 *
 * This filters the solr results for a specific collection
 *
 * @see islandora_solr()
 */
function islandora_dss_solr_process_islandora_solr(&$vars) {

  global $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP;
  $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP = array('McKelvy House Photograph Collection' => array('dc.title' => 'Title',
												  'geology_slides_esi.subject.sort' => 'Subject',
												  'mdl_prints.format.medium.sort' => 'Medium',
												  'mckelvy.date.original.display' => 'Publication Date',
												  ),
						   
						   'Lafayette World War II Casualties' => array('dc.title' => 'Name',
												'war_casualties.description.class.sort' => 'Graduating Class',
												'war_casualties.description.military.branch.sort' => 'Military Branch',
												'war_casualties.contributor.military.unit.sort' => 'Military Unit',
												),

						   'Historical Photograph Collection' => array('dc.title' => 'Title',
											       'dc.subject.sort' => 'Subject',
											       'dc.date.sort' => 'Publication Date',
											       'dc.type.sort' => 'Medium'
											       ),

						   'Marquis de Lafayette Prints Collection' => array('dc.title' => 'Title',
												     'mdl_prints.creator.sort' => 'Creator',
												     'mdl_prints.format.medium.sort' => 'Format.Medium',
												     'mdl_prints.description.series.sort' => 'Description.Series',
												     'mdl_prints.date.original.sort' => 'Date.Original',
												     'mdl_prints.subject.lcsh.sort' => 'Subject.LCSH'
												     ),

						   'Geology Department Slide Collection' => array('dc.title' => 'Title',
												  'geology_slides_esi.subject.sort' => 'Subject',
												  'geology_slides_esi.date.original.sort' => 'Publication Date',
												  'geology_slides_esi.coverage.location.sort' => 'Coverage'
												  ),

						   'East Asia Image Collection' => array('dc.title' => 'Title.English',
											 'eastasia.Subject.OCM.sort' => 'Subject.OCM',
											 'eastasia.Date.Artifact.Lower' => 'Date.Artifact.Lower',
											 'eastasia.Date.Artifact.Upper' => 'Date.Artifact.Upper',
											 'eastasia.Coverage.Location.Country.sort' => 'Coverage.Location.Country',
											 'eastasia.Creator.Maker.sort' => 'Creator.Maker',
											 'cdm.Relation.IsPartOf.sort' => 'Relation.IsPartOf',
											 'eastasia.Format.Medium.sort' => 'Format.Medium',
											 ),

						   'Lafayette Newspaper Collection' => array('dc.title' => 'Title',
											     'dc.date.sort' => 'Publication Date'),

						   'Lafayette Magazine Collection' => array(
											    'MODS.mods.identifier.local_i' => 'Publication Sequence',
											    'MODS.mods.titleInfo_ss' => 'Title',
											    'MODS.mods.originInfo.publisher_ss' => 'Publisher',
											    'MODS.mods.relatedItem.titleInfo.title_ss' => 'Publication Title', // Changing this label from "Series" to "Publication Title" in accordance with DSSSM-1177
											    ),
						   'Shakespeare Bulletin Archive' => array(
											   'MODS.mods.relatedItem.date.w3cdtf_dts' => 'Date',
											   'MODS.mods.titleInfo_ss' => 'Title'
											   )
						   );

  global $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP;
  $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP = array('Lafayette World War II Casualties' => array('dc.title' => 'Name',
												    'war_casualties.description.class' => 'Graduating Class',
												    'war_casualties.description.military.branch' => 'Military Branch',
												    'war_casualties.contributor.military.unit' => 'Military Unit',
												    ),

						       'Historical Photograph Collection' => array('dc.title' => 'Title',
												   'dc.subject' => 'Subject',
												   'dc.date' => 'Publication Date',
												   'dc.type' => 'Medium'
												   ),

						       'Marquis de Lafayette Prints Collection' => array('dc.title' => 'Title',
													 'mdl_prints.creator' => 'Creator',
													 'mdl_prints.subject.lcsh' => 'Subject.LCSH',
													 'mdl_prints.format.medium' => 'Format.Medium',
													 'mdl_prints.description.series' => 'Description.Series',
													 'mdl_prints.date.original' => 'Date.Original'
													 ),

						       // Cannot sort on multivalue fields (e. g. subject)
						       'Geology Department Slide Collection' => array('dc.title' => 'Title',
												      'geology_slides_esi.subject' => 'Subject',
												      'geology_slides_esi.date.original' => 'Publication Date',
												      'eastasia.Coverage.Location' => 'Coverage'),

						       'East Asia Image Collection' => array('dc.title' => 'Title.English',
											     'eastasia.Subject.OCM' => 'Subject.OCM',
											     //'eastasia.Date.Artifact.Lower' => 'Date.Artifact.Lower',
											     //'eastasia.Date.Artifact.Upper' => 'Date.Artifact.Upper',
											     'eastasia.Coverage.Location.Country' => 'Coverage.Location.Country',
											     //'eastasia.Format.Medium' => 'Format.Medium',
											     'eastasia.Creator.Maker' => 'Creator.Maker',
											     'cdm.Relation.IsPartOf' => 'Relation.IsPartOf',
											     ),

						       'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
												      'geology_slides_esi.subject' => 'Subject',
												      'eastasia.Format.Medium' => 'Medium',
												      'mckelvy.date.original.display' => 'Publication Date'),

						       'Lafayette Newspaper Collection' => array('dc.title' => 'Title',
												 'dc.date' => 'Publication Date',
												 'dc.coverage' => 'Coverage'),

						       'Lafayette Magazine Collection' => array(
												'MODS.mods.titleInfo_s' => 'Title',
												'MODS.mods.relatedItem.date.w3cdtf_dts' => 'Date',

												'MODS.mods.relatedItem.part.date.approximate_s' => 'Date',
												'MODS.mods.relatedItem.originInfo.dateIssued.approximate_s' => 'Date',

												'MODS.mods.originInfo.publisher_s' => 'Publisher',
												'MODS.mods.relatedItem.titleInfo.title_s' => 'Publication Title', // Changing this label from "Series" to "Publication Title" in accordance with DSSSM-1177
												),
						       'Shakespeare Bulletin Archive' => array(
											       'MODS.mods.titleInfo_s' => 'Title',
											       'MODS.mods.relatedItem.part.date.approximate_s' => 'Date',
											       'MODS.mods.originInfo.publisher_s' => 'Publisher',
											       'MODS.mods.relatedItem.titleInfo.title_s' => 'Series',
											       )

						       );

  $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP['Mckelvy House Photograph Collection'] = $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP['McKelvy House Photograph Collection'];

  /*
   * Hard-coding for IP-based restrictions for Solr results
   * @todo Refactor with XACML policy restrictions (extend for integrating permitted roles)
   * @todo Integrate with admin. menus
   * This assumes a subnet of 139.147.0.0/16 for Lafayette College servers
   * This assumes a subnet of 192.168.101.0/24 for the VPN
   *
   */
  $vars['restricted_results'] = false;

  $client_ip = ip_address();
  $headers = apache_request_headers();

  $ip_ranges = variable_get('islandora_dss_solr_ip_ranges', array('192.168.101.0/24', '139.147.0.0/16'));

  // ...not within the campus network...

  // (for proxy servers...)
  if(array_key_exists('X-Forwarded-For', $headers)) {

    // Not on the VPN...
    $is_anon_non_lafayette_user = !islandora_dss_solr_net_match($ip_ranges[0], $headers['X-Forwarded-For']);
    $is_anon_non_lafayette_user &= (bool) !islandora_dss_solr_net_match($ip_ranges[1], $headers['X-Forwarded-For']);
  } else {

    // Not on the VPN...
    $is_anon_non_lafayette_user = !islandora_dss_solr_net_match($ip_ranges[0], $client_ip);
    $is_anon_non_lafayette_user &= (bool) !islandora_dss_solr_net_match($ip_ranges[1], $client_ip);
  }

  $is_anon_non_lafayette_user &= !user_is_logged_in(); // ...and not authenticated.

  // Fully resolves DSS-280
  $is_anon_non_lafayette_user = (bool) $is_anon_non_lafayette_user;

  foreach($vars['results'] as &$result ) {

    $result['restricted'] = false;

    if(array_key_exists('cdm.Relation.IsPartOf', $result['solr_doc'])) {

      $collections = explode(', ', $result['solr_doc']['cdm.Relation.IsPartOf']['value']);
    } elseif(array_key_exists('dc.relation', $result['solr_doc'])) {

      $collections = explode(', ', $result['solr_doc']['dc.relation']['value']);
    } else {

      $collections = array('Historical Photograph Collection');
    }
    $top_collection = array_shift($collections);

    /**
     * Hard-coding access control based upon metadata field value
     * @todo Refactor for XACML integration
     *
     */
    if($top_collection == 'Geology Department Slide Collection' and $is_anon_non_lafayette_user) {
	 
      $result['restricted'] = true;
      $vars['restricted_results'] = true;
    }

    global $ISLANDORA_DSS_SOLR_TOP_COLLECTION;
    $ISLANDORA_DSS_SOLR_TOP_COLLECTION = $top_collection;

    $collection_fields = array_keys($ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP[$top_collection]);

    //$vars['collection_fields'] = $collection_fields;
    $vars['collection_fields'] = $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP[$top_collection];

    if(count($collection_fields) != count(array_keys($result['solr_doc']))) {

      // Refactor
      $ISLANDORA_DSS_SOLR_DATE_FIELDS = array('dc.date',
					      'geology_slides_esi.date.original',
					      'mckelvy.date.original.display',
					      'mdl_prints.date.original',
					      'MODS.mods.relatedItem.date.w3cdtf_dts');

      foreach($collection_fields as $collection_field) {

	/**
	 * Transformations unique to the Alumni Publications Collection and the Shakespeare Bulletin Archive
	 *
	 */
	if(in_array($top_collection, array('Lafayette Magazine Collection', 'Shakespeare Bulletin Archive'))) {

	  // Ensure that only the natural language date value is rendered for the field "Date"
	  if(in_array($top_collection, array('Lafayette Magazine Collection'))) {
	    
	    if(in_array($collection_field, array('MODS.mods.relatedItem.part.date.approximate_s',
						 'MODS.mods.relatedItem.originInfo.dateIssued.approximate_s'))) {

	      if(!empty($result['solr_doc'][$collection_field]['value'])) {

		if(!empty($result['solr_doc']['MODS.mods.relatedItem.date.w3cdtf_dts']['value'])) {

		  $result['solr_doc']['MODS.mods.relatedItem.date.w3cdtf_dts']['value'] = $result['solr_doc'][$collection_field]['value'];
		  unset($result['solr_doc'][$collection_field]);
		} else {
		
		  $result['solr_doc']['MODS.mods.relatedItem.date.w3cdtf_dts'] = array('label' => $result['solr_doc'][$collection_field]['label'],
										       'class' => 'mods-mods-relateditem-date-w3cdtf-dts',
										       'value' => $result['solr_doc'][$collection_field]['value']
										       );

		  $ISLANDORA_DSS_SOLR_DATE_FIELDS = array_diff($ISLANDORA_DSS_SOLR_DATE_FIELDS, array('MODS.mods.relatedItem.date.w3cdtf_dts'));
		  unset($result['solr_doc'][$collection_field]);
		}
	      } elseif(array_key_exists($collection_field, $result['solr_doc'])) {
		
		unset($result['solr_doc'][$collection_field]);
	      }
	    }
	  }

	  // Ensure that multiple values for the field "Series" are rendered within separate rows
	  if(in_array($collection_field, array('MODS.mods.relatedItem.titleInfo.title_s'))) {

	    $field_values = explode(',', $result['solr_doc'][$collection_field]['value']);
	    $result['solr_doc'][$collection_field]['value'] = array_shift($field_values);

	    // For cases in which the volume of the <relatedItem> entity can be rendered, append the value (within parentheses) to the field value itself
	    if(!empty($result['solr_doc']['MODS.mods.relatedItem.part.text.volume_s']['value'])) {

	      $result['solr_doc'][$collection_field]['value'] .= ' (vol. ' . $result['solr_doc']['MODS.mods.relatedItem.part.text.volume_s']['value'] . ')';
	      
	      // For cases in which the issue of the <relatedItem> entity can, also, be rendered, append the value (within parentheses) to the field value itself
	      if(!empty($result['solr_doc']['MODS.mods.relatedItem.part.text.issue_s']['value'])) {

		$result['solr_doc'][$collection_field]['value'] = rtrim($result['solr_doc'][$collection_field]['value'], ')');
		$result['solr_doc'][$collection_field]['value'] .= ', no. ' . $result['solr_doc']['MODS.mods.relatedItem.part.text.issue_s']['value'] . ')';
	      }

	    } elseif(!empty($result['solr_doc']['MODS.mods.relatedItem.date.w3cdtf_dts']['value'])) {

	      if(in_array($top_collection, array('Shakespeare Bulletin Archive'))) {
		
		$result['solr_doc'][$collection_field]['value'] .= ' (' . $result['solr_doc']['MODS.mods.relatedItem.part.date.approximate_s']['value'] . ')';
	      } else {
		
		// For cases in which neither the volume nor issue can be rendered, simply render the date
		$result['solr_doc'][$collection_field]['value'] .= ' (' . $result['solr_doc']['MODS.mods.relatedItem.date.w3cdtf_dts']['value'] . ')';
	      }
	    }

	    // Render the multiple values for "Series" as multiple fields
	    foreach($field_values as $i => $field_value) {

	      $field_key = $collection_field . '_' . $i;
	      if(!empty($result['solr_doc']['MODS.mods.relatedItem.date.w3cdtf_dts']['value'])) {

		$field_value .= ' (' . $result['solr_doc']['MODS.mods.relatedItem.date.w3cdtf_dts']['value'] . ')';
	      }

	      $result['solr_doc'][$field_key] = array('label' => $result['solr_doc'][$collection_field]['label'],
						      'value' => $field_value,
						      'class' => '');
	      $collection_fields[] = $field_key;
	    }
	  }
	}

	// Trim the leading whitespace for the title field, and render this as a link
	// This resolves DSSSM-1093
	if(in_array($collection_field, array('MODS.mods.titleInfo_s'))) {

	  $result['solr_doc'][$collection_field]['value'] = ltrim($result['solr_doc'][$collection_field]['value'], ' ');

	  // Ensure that the value links to the Object within Fedora Commons
	  // This resolves DSSSM-1093
	  $options = array('html' => TRUE);

	  if(isset($result['object_url_params'])) {

	    $options['query'] = $result['object_url_params'];
	  }
	    
	  if(isset($result['object_url_fragment'])) {

	    $options['fragment'] = $result['object_url_fragment'];
	  }

	  /**
	   * Modifying the links for Objects retrieved during full-text searches in order to ensure that the "q" parameter contains the search string
	   * DSSSM-1117
	   *
	   */
	  if(preg_match('/foxml\.all\.text\:\((".+?")\)/', $_GET['q'], $query_match)) {
	    
	    $full_text_query = $query_match[1];
	    $result['solr_doc'][$collection_field]['value'] = l($result['solr_doc'][$collection_field]['value'],
								drupal_get_path_alias($result['object_url']),
								array_merge($options, array('query' => array('search' => $full_text_query)))
								);

	  } else {

	    $result['solr_doc'][$collection_field]['value'] = l($result['solr_doc'][$collection_field]['value'], drupal_get_path_alias($result['object_url']), $options);
	  }
	}
      

	if(!array_key_exists($collection_field, $result['solr_doc']) and $top_collection != 'Lafayette Magazine Collection') {

	  $result['solr_doc'][$collection_field] = array('label' => islandora_dss_solr_dc_label_map($top_collection, $collection_field),
							 'value' => '',
							 'class' => '');
	  
	} elseif(in_array($collection_field, $ISLANDORA_DSS_SOLR_DATE_FIELDS)) { // Format date field values

	  // Ensure that, if there are multiple dates present, that only the first value is formatted
	  $result['solr_doc'][$collection_field]['value'] = array_shift(explode(',', $result['solr_doc'][$collection_field]['value']));
	  //$result['solr_doc'][$collection_field]['value'] = gmdate('Y-m-d', strtotime($result['solr_doc'][$collection_field]['value']));

	  /**
	   * Restructuring the date values for decades within the Historical Photograph Collection
	   * Resolves DSSSM-885
	   *
	   */
	  //$result['solr_doc'][$collection_field]['value'] = gmdate('Y-m-d', strtotime($result['solr_doc'][$collection_field]['value']));
	  $date_value = new DateTime($result['solr_doc'][$collection_field]['value'], new DateTimeZone('GMT'));
	  $result['solr_doc'][$collection_field]['value'] = $date_value->format('Y-m-d');

	  /**
	   * Addressing the issue for ...
	   * Resolves DSSSM-885
	   */
	  if($top_collection == 'Historical Photograph Collection' or
	     $top_collection == 'McKelvy House Photograph Collection') {

	    if($date_value->format('m-d') == '01-01') {

	      $result['solr_doc'][$collection_field]['value'] = $date_value->format('Y');
	      if(preg_match('/\d0/', $date_value->format('y')) and $top_collection == 'Historical Photograph Collection') {

		$result['solr_doc'][$collection_field]['value'] .= "'s";
	      }
	    }
	  }
	}
      }
    }

    /**
     * Specialized handling for reordering the fields based upon the parent collection of the Object
     *
     */
    if($top_collection == 'Lafayette Magazine Collection') {

      $collection_fields = array_diff($collection_fields, array('MODS.mods.relatedItem.part.date.approximate_s', 'MODS.mods.relatedItem.originInfo.dateIssued.approximate_s'));
    }

    /**
     * Sort the field labels based upon a custom array
     *
     */
    // Reorder the fields
    $sorted_doc = array();

    foreach($collection_fields as $field) {

      $sorted_doc[$field] = $result['solr_doc'][$field];
    }
    $result['solr_doc'] = $sorted_doc;

    // Replacing certain Dublin Core field values with the appropriate value
    // (e. g. replacing MARC relator values)
    foreach($result['solr_doc'] as $field => &$value) {

      /**
       * Work-around for the Alumni Publications
       * @todo Refactor
       *
       */
      if(!preg_match('/MODS.mods.relatedItem.titleInfo.title_s_/', $field)) {

	if(!islandora_dss_solr_dc_label_map($top_collection, $field)) {

	  unset($result['solr_doc'][$field]);
	} else {

	  $value['label'] = islandora_dss_solr_dc_label_map($top_collection, $field);
	}
      }
    }
  }

  drupal_add_js(libraries_get_path('jquery-ui-touch-punch') . '/jquery.ui.touch-punch.min.js');

  //drupal_add_js(array('islandoraDssSolrFacetPages' => array('pathAlias' => http_build_query($_GET)), 'setting'));

  drupal_add_js(array('islandoraDssSolrFacetPages' => array('query' => $_GET['q'])), 'setting');

  if(array_key_exists('f', $_GET)) {

    drupal_add_js(array('islandoraDssSolrFacetPages' => array('facets' => http_build_query($_GET['f']))), 'setting');
  }
}

/**
 * Implements hook_process_HOOK().
 * This is passed for handling within the theming layer for islandora_solr functionality
 *
 */
function islandora_dss_solr_process_islandora_solr_wrapper(&$vars) {

  global $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP;
  global $ISLANDORA_DSS_SOLR_TOP_COLLECTION;

  if(!$ISLANDORA_DSS_SOLR_TOP_COLLECTION) {

    $collection_fields = array();
  } else {

    $collection_fields = $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP[$ISLANDORA_DSS_SOLR_TOP_COLLECTION];
  }

  $vars['collection_fields'] = $collection_fields;
}

/**
 * Implements hook_preprocess_html()
 *
 */
function islandora_dss_solr_preprocess_html(&$vars) {

  /**
   * Set a static title for Islandora Solr search results
   * Resolves 
   * @todo Refactor for admin interface with variable_get()
   *
   */
  if(preg_match('/islandora\/search/', current_path())) {

    $vars['head_title'] = t("DSS Search Results") . ' | ' . $vars['head_title_array']['name'];
  }
}

/**
 * Implements hook_theme_alter().
 * @author griffinj
 *
 * @see islandora_solr_theme()
 *
 */

function islandora_dss_solr_theme() {

  // set path
  $path = drupal_get_path('module', 'islandora_dss_solr');
  $file = 'theme.inc';

  return array(
	       // advanced solr search form/block
	       'islandora_dss_solr_advanced_search_form' => array('variables' => array('form' => NULL,),),
	       );
}
