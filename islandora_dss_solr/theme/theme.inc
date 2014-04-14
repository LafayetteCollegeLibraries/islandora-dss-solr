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

  /*
			<!-- war_casualties.description.cause.death -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='cause-death']">
			  <field name="war_casualties.description.cause.death">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.contributor.military.unit -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='military-unit']">
			  <field name="war_casualties.contributor.military.unit">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.description.class -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='lafayette-class']">
			  <field name="war_casualties.description.class">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.description.honors -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='military-honors']">
			  <field name="war_casualties.description.honors">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.description.military.branch -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='military-branch']">
			  <field name="war_casualties.description.military.branch">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.description.military.rank -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='military-rank']">
			  <field name="war_casualties.description.military.rank">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.coverage.place.birth -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='place-birth']">
			  <field name="war_casualties.coverage.place.birth">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.coverage.place.death -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='place-death']">
			  <field name="war_casualties.coverage.place.death">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.format.analog -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:physicalDescription/mods:note[@type='format-analog']">
			  <field name="war_casualties.format.analog">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
   */

$ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP = array();

/*
						       'Lafayette Newspaper Collection' => array('dc.title' => 'Title',
												 'dc.date' => 'Date',
												 'dc.coverage' => 'Coverage')
 */
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
												  'dc.type.sort' => 'Format.Medium',
												  'mckelvy.date.original.display' => 'Date.Original',
												  ),
						   
						   'Lafayette World War II Casualties' => array('dc.title' => 'Name',
												'war_casualties.description.class.sort' => 'Description.Class',
												'war_casualties.description.military.branch.sort' => 'Description.Military.Branch',
												'war_casualties.contributor.military.unit.sort' => 'Description.Military.Unit',
												),

						   'Historical Photograph Collection' => array('dc.title' => 'Title',
											       'dc.subject.sort' => 'Subject',
											       'dc.date.sort' => 'Date',
											       'dc.type.sort' => 'Type'
											       ),

						   'Marquis de Lafayette Prints Collection' => array('dc.title' => 'Title',
												     'mdl_prints.creator.sort' => 'Creator',
												     //'mdl_prints.subject.lcsh.sort' => 'Subject.LCSH',
												     'mdl_prints.format.medium.sort' => 'Format.Medium',
												     'mdl_prints.description.series.sort' => 'Description.Series',
												     'mdl_prints.date.original.sort' => 'Date.Original'
												     ),

						   'Geology Department Slide Collection' => array('dc.title' => 'Title',
												  'geology_slides_esi.subject.sort' => 'Subject',
												  'geology_slides_esi.date.original.sort' => 'Date.Original',
												  'eastasia.Coverage.Location.sort' => 'Coverage.Location'
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
											     'dc.date.sort' => 'Date',
											     'dc.coverage.sort' => 'Coverage')
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
												      'geology_slides_esi.date.original' => 'Date.Original',
												      'eastasia.Coverage.Location' => 'Coverage.Location'),

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
												      'eastasia.Format.Medium' => 'Format.Medium',
												      'mckelvy.date.original.display' => 'Date'),

						       'Lafayette Newspaper Collection' => array('dc.title' => 'Title',
												 'dc.date' => 'Date',
												 'dc.coverage' => 'Coverage')
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
  $is_anon_non_lafayette_user = !islandora_dss_solr_net_match('192.168.101.0/24', $client_ip) and // Not on the VPN...
    !islandora_dss_solr_net_match('139.147.0.0/16', $client_ip) and // ...not within the campus network...
    !user_is_logged_in(); // ...and not authenticated.

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
      $ISLANDORA_DSS_SOLR_DATE_FIELDS = array('dc.date', 'geology_slides_esi.date.original', 'mckelvy.date.original.display', 'mdl_prints.date.original');

      foreach($collection_fields as $collection_field) {

	if(!array_key_exists($collection_field, $result['solr_doc'])) {

	  $result['solr_doc'][$collection_field] = array('label' => islandora_dss_solr_dc_label_map($top_collection, $collection_field),
							 'value' => '',
							 'class' => '');
	} elseif(in_array($collection_field, $ISLANDORA_DSS_SOLR_DATE_FIELDS)) { // Format date field values

	  // Ensure that, if there are multiple dates present, that only the first value is formatted
	  $result['solr_doc'][$collection_field]['value'] = array_shift(explode(',', $result['solr_doc'][$collection_field]['value']));

	  $result['solr_doc'][$collection_field]['value'] = gmdate('Y-m-d', strtotime($result['solr_doc'][$collection_field]['value']));
	}
      }
    }

    foreach($result['solr_doc'] as $field => &$value) {

      if(! islandora_dss_solr_dc_label_map($top_collection, $field)) {

	unset($result['solr_doc'][$field]);
      } else {

	$value['label'] = islandora_dss_solr_dc_label_map($top_collection, $field);
      }
    }
  }

  drupal_add_js(libraries_get_path('jquery-ui-touch-punch') . '/jquery.ui.touch-punch.min.js');

  dpm(http_build_query($_GET));
  dpm( rawurldecode(http_build_query($_GET)));

  //drupal_add_js(array('islandoraDssSolrFacetPages' => array('pathAlias' => http_build_query($_GET)), 'setting'));

  drupal_add_js(array('islandoraDssSolrFacetPages' => array('query' => $_GET['q'])), 'setting');

  if(array_key_exists('f', $_GET)) {

    drupal_add_js(array('islandoraDssSolrFacetPages' => array('facets' => http_build_query($_GET['f']))), 'setting');
  }
}

function islandora_dss_solr_process_islandora_solr_wrapper(&$vars) {

  //global $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP;
  global $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP;
  global $ISLANDORA_DSS_SOLR_TOP_COLLECTION;

  /*
  $result = array_shift($vars['results']);
  $collections = explode(', ', $result['solr_doc']['cdm.Relation.IsPartOf']['value']);
  $top_collection = array_shift($collections);
  */

  if(!$ISLANDORA_DSS_SOLR_TOP_COLLECTION) {

    $collection_fields = array();
  } else {

    $collection_fields = $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP[$ISLANDORA_DSS_SOLR_TOP_COLLECTION];
  }

  $vars['collection_fields'] = $collection_fields;
}

function islandora_dss_solr_preprocess_html(&$vars) {

  /**
   * Set a static title for Islandora Solr search results
   * Resolves 
   * @todo Refactor for admin interface with variable_get()
   *
   */
  //drupal_set_title('DSS Search Results');

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
