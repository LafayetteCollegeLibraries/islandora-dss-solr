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

$ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP = array(
						 'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
												'dc.subject' => 'Subject',
												'mckelvy.date.original.display' => 'mckelvy.date.original.display',
												'dc.type' => 'Type'
											     ),
						 'Lafayette World War II Casualties' => array(
											      'dc.title' => 'Title.name',
											      'war_casualties.description.class' => 'Description.class',
											      'war_casualties.description.military.branch' => 'Description.military.branch',
											      'war_casualties.contributor.military.unit' => 'Description.military.unit',
											      ),
						 'Historical Photograph Collection' => array('dc.title' => 'Title',
											     'dc.subject' => 'Subject',
											     'dc.date' => 'Date',
											     'dc.type' => 'Type'
											     ),

						 'Marquis de Lafayette Prints Collection' => array('dc.title' => 'Title',
												   'mdl_prints.creator' => 'Creator',
												   'mdl_prints.subject.lcsh' => 'Subject.LCSH',
												   'mdl_prints.format.medium' => 'Format.Medium',
												   'mdl_prints.description.series' => 'Description.Series',
												   'mdl_prints.date.original' => 'Date.Original'
												   ),
						 'Geology Department Slide Collection' => array('dc.title' => 'Title',
												//'geology_slides_esi.subject ' => 'Subject',
												'geology_slides_esi.date.original' => 'Date.Original',
												//'eastasia.Coverage.Location' => 'Coverage.Location'
												),
						 'East Asia Image Collection' => array('dc.title' => 'Title.English',
										       //'eastasia.Subject.OCM' => 'Subject.OCM',
										       'eastasia.Date.Artifact.Lower' => 'Date.Artifact.Lower',
										       'eastasia.Date.Artifact.Upper' => 'Date.Artifact.Upper',
										       //'eastasia.Coverage.Location.Country' => 'Coverage.Location.Country',
										       //'eastasia.Format.Medium' => 'Format.Medium',
										       //'eastasia.Creator.Maker' => 'Creator.Maker')
										       )
						 );

$ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP = array(
						     'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
												    'dc.subject' => 'Subject',
												    'mckelvy.date.original.display' => 'mckelvy.date.original.display',
												    'dc.type' => 'Type'
											     ),
						 //'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
						 //'dc.subject' => 'Subject',
						 //'dc.date' => 'Date',
						 //'dc.type' => 'Type'
						 //),
						     'Lafayette World War II Casualties' => array(
												  'dc.title' => 'Title.name',
												  'war_casualties.description.class' => 'Description.class',
												  'war_casualties.description.military.branch' => 'Description.military.branch',
												  'war_casualties.contributor.military.unit' => 'Description.military.unit',
												  ),
						     'Historical Photograph Collection' => array('dc.title' => 'Title',
												 'dc.subject' => 'Subject',
												 'dc.date' => 'Date',
												 'dc.type' => 'Type'
												 ),
						     'Marquis de Lafayette Prints Collection' => array('dc.title' => 'Title',
												       'mdl_prints.creator' => 'Creator',
												       'mdl_prints.subject.lcsh' => 'Subject.LCSH',
												       'mdl_prints.format.medium' => 'Format.Medium',
												       'mdl_prints.description.series' => 'Description.Series',
												       'mdl_prints.date.original' => 'Date.Original'
												       ),
						     'Geology Department Slide Collection' => array('dc.title' => 'Title',
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

function islandora_dss_solr_dc_label_map($collection, $dc_field) {

  /*
Subject.OCM
Date.Artifact.Lower
Date.Artifact.Upper
Coverage.Location.Country
Format.Medium
Creator.Maker

   */

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
 * hook_process function for islandora_solr
 *
 * This filters the solr results for a specific collection
 *
 * @see islandora_solr()
 */
function islandora_dss_solr_process_islandora_solr(&$vars) {

  global $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP;
  $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP = array(
						     'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
												    'dc.subject' => 'Subject',
												    'mckelvy.date.original.display' => 'mckelvy.date.original.display',
												    'dc.type' => 'Type'
											     ),
						     //'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
						     //'dc.subject' => 'Subject',
						     //'dc.date' => 'Date',
						     //'dc.type' => 'Type'
						     //),
						   'Lafayette World War II Casualties' => array(
												'dc.title' => 'Title.name',
												'war_casualties.description.class' => 'Description.class',
												'war_casualties.description.military.branch' => 'Description.military.branch',
												'war_casualties.contributor.military.unit' => 'Description.military.unit',
												),
						   'Historical Photograph Collection' => array('dc.title' => 'Title',
											       'dc.subject' => 'Subject',
											       'dc.date' => 'Date',
											       'dc.type' => 'Type'
											       ),
						   'Marquis de Lafayette Prints Collection' => array('dc.title' => 'Title',
												     'mdl_prints.creator' => 'Creator',
												     'mdl_prints.subject.lcsh' => 'Subject.LCSH',
												     'mdl_prints.format.medium' => 'Format.Medium',
												     'mdl_prints.description.series' => 'Description.Series',
												     'mdl_prints.date.original' => 'Date.Original'
												     ),

						   'Geology Department Slide Collection' => array('dc.title' => 'Title',
												  //'geology_slides_esi.subject ' => 'Subject',
												  'geology_slides_esi.date.original' => 'Date.Original',
												  //'eastasia.Coverage.Location' => 'Coverage.Location'
												  ),
						   'East Asia Image Collection' => array('dc.title' => 'Title.English',
											 //'eastasia.Subject.OCM' => 'Subject.OCM',
											 'eastasia.Date.Artifact.Lower' => 'Date.Artifact.Lower',
											 'eastasia.Date.Artifact.Upper' => 'Date.Artifact.Upper',
											 //'eastasia.Coverage.Location.Country' => 'Coverage.Location.Country',
											 //'eastasia.Format.Medium' => 'Format.Medium',
											 //'eastasia.Creator.Maker' => 'Creator.Maker')
											 ),

						     'Lafayette Newspaper Collection' => array('dc.title' => 'Title',
											       'dc.date' => 'Date',
											       'dc.coverage' => 'Coverage')
						   );

  global $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP;
  $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP = array(
						       'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
												      'dc.subject' => 'Subject',
												      'mckelvy.date.original.display' => 'mckelvy.date.original.display',
												      'dc.type' => 'Type'
												      ),

						       //'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
						       //'dc.subject' => 'Subject',
						       //'dc.date' => 'Date',
						       //'dc.type' => 'Type'
						       //),
						       'Lafayette World War II Casualties' => array(
												    'dc.title' => 'Title.name',
												    'war_casualties.description.class' => 'Description.class',
												    'war_casualties.description.military.branch' => 'Description.military.branch',
												    'war_casualties.contributor.military.unit' => 'Description.military.unit',
												    ),
						       'Historical Photograph Collection' => array('dc.title' => 'Title',
												   'dc.subject' => 'Subject',
												   'dc.date' => 'Date',
												   'dc.type' => 'Type'
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
											     'eastasia.Date.Artifact.Lower' => 'Date.Artifact.Lower',
											     'eastasia.Date.Artifact.Upper' => 'Date.Artifact.Upper',
											     'eastasia.Coverage.Location.Country' => 'Coverage.Location.Country',
											     'eastasia.Format.Medium' => 'Format.Medium',
											     'eastasia.Creator.Maker' => 'Creator.Maker'),

						       'McKelvy House Photograph Collection' => array('dc.title' => 'Title',
												      'dc.subject' => 'Subject',
												      'eastasia.Format.Medium' => 'Format.Medium',
												      'mckelvy.date.original.display' => 'Date'),

						       'Lafayette Newspaper Collection' => array('dc.title' => 'Title',
												 'dc.date' => 'Date',
												 'dc.coverage' => 'Coverage')
						       );

  $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP['Mckelvy House Photograph Collection'] = $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP['McKelvy House Photograph Collection'];

  /*
dc,title
dc.subject
dc.format.medium
date.original.display
   */

  foreach($vars['results'] as &$result ) {

    //dpm($result['solr_doc']);
    //dpm($result);

    if(array_key_exists('cdm.Relation.IsPartOf', $result['solr_doc'])) {

      $collections = explode(', ', $result['solr_doc']['cdm.Relation.IsPartOf']['value']);
    } elseif(array_key_exists('dc.relation', $result['solr_doc'])) {

      $collections = explode(', ', $result['solr_doc']['dc.relation']['value']);
    } else {

      $collections = array('Historical Photograph Collection');
    }
    $top_collection = array_shift($collections);

    global $ISLANDORA_DSS_SOLR_TOP_COLLECTION;
    $ISLANDORA_DSS_SOLR_TOP_COLLECTION = $top_collection;

    $collection_fields = array_keys($ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP[$top_collection]);

    //$vars['collection_fields'] = $collection_fields;
    $vars['collection_fields'] = $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP[$top_collection];

    if(count($collection_fields) != count(array_keys($result['solr_doc']))) {

      foreach($collection_fields as $collection_field) {

	if(!array_key_exists($collection_field, $result['solr_doc'])) {

	  $result['solr_doc'][$collection_field] = array('label' => islandora_dss_solr_dc_label_map($top_collection, $collection_field),
							 'value' => '',
							 'class' => '');
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
}

function islandora_dss_solr_process_islandora_solr_wrapper(&$vars) {

  //global $ISLANDORA_DSS_SOLR_COLLECTIONS_DC_LABEL_MAP;
  global $ISLANDORA_DSS_SOLR_COLLECTIONS_SORT_MAP;
  global $ISLANDORA_DSS_SOLR_TOP_COLLECTION;

  dpm($vars);

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
  dpm($collection_fields);

  $vars['collection_fields'] = $collection_fields;
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
