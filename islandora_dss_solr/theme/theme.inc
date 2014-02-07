<?php

  /**
   * @file Hook implementations for theming
   * @author griffinj@lafayette.edu
   *
   */

  /*
title
subject
date.original
coverage.location
  */



function islandora_dss_solr_dc_label_map($collection, $dc_field) {

  /*
Subject.OCM
Date.Artifact.Lower
Date.Artifact.Upper
Coverage.Location.Country
Format.Medium
Creator.Maker

   */

  $COLLECTIONS_DC_LABEL_MAP = array(
'Geology Department Slide Collection, John S. Shelton Earth Science Image Collection' => array('dc.title' => 'Title',
											       'geology_slides_esi.subject ' => 'Subject',
											       'geology_slides_esi.date.original' => 'Date.Original',
											       'eastasia.Coverage.Location' => 'Coverage.Location'),
'East Asia Image Collection' => array('dc.title' => 'Title.English',
				      'eastasia.Subject.OCM' => 'Subject.OCM',
				      'eastasia.Date.Artifact.Lower' => 'Date.Artifact.Lower',
				      'eastasia.Date.Artifact.Upper' => 'Date.Artifact.Upper',
				      'eastasia.Coverage.Location.Country' => 'Coverage.Location.Country',
				      'eastasia.Format.Medium' => 'Format.Medium',
				      'eastasia.Creator.Maker' => 'Creator.Maker')
				    );

  if(array_key_exists($collection, $COLLECTIONS_DC_LABEL_MAP)) {

    if(array_key_exists($dc_field, $COLLECTIONS_DC_LABEL_MAP[$collection])) {

      return $COLLECTIONS_DC_LABEL_MAP[$collection][$dc_field];
    }
  }

  return NULL;
}

/**
 * hook_process function for islandora_solr
 *
 * This filters the solr results for a specific collection
 *
 * @see islandora_solr()
 */
function islandora_dss_solr_process_islandora_solr(&$vars) {

  foreach($vars['results'] as &$result ) {

    foreach($result['solr_doc'] as $field => &$value) {

      if(! islandora_dss_solr_dc_label_map($result['solr_doc']['cdm.Relation.IsPartOf']['value'], $field)) {

	unset($result['solr_doc'][$field]);
      } else {

	$value['label'] = islandora_dss_solr_dc_label_map($result['solr_doc']['cdm.Relation.IsPartOf']['value'], $field);
      }
    }
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
