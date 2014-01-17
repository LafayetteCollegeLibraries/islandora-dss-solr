<?php

  /**
   * @file Hook implementations for theming
   * @author griffinj@lafayette.edu
   *
   */

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

      //$value['value'] = preg_replace('/,/', '<br />', $value['value']);
    }
  }

  //dpm($vars['results']);
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
