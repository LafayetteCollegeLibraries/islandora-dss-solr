/**
 * @file Functionality for basic UI features for the Islandora DSS Solr features   
 * @author griffinj@lafayette.edu
 *
 *
 */

"use strict";

/**
 * Drupal integration
 *
 */
(function($, Drupal) {

    Drupal.behaviors.islandoraDssSolr = {

	attach: function(context, settings) {

	    var ISLANDORA_DSS_SOLR_DATE_FIELDS = [
						  'dc.date',
						  'eastasia.Date.Artifact.Lower',
						  'eastasia.Date.Artifact.Upper',
						  'eastasia.Date.Image.Lower',
						  'eastasia.Date.Image.Upper',
						  'eastasia.Date.Original',
						  'geology_slides_esi.date.original',
						  'mdl_prints.date.original',
						  'war_casualties.date.birth.display',
						  'war_casualties.date.death.display',
						  'mckelvy.date.original.search',
						  ];

	    $('.islandora-solr-search-field option').click(function(e) {

		    if(ISLANDORA_DSS_SOLR_DATE_FIELDS.indexOf( $(this).val() ) !== -1) {

			$(this).parents('.fieldset-wrapper').find('.form-text')
			.val('Ex. 1925, 1925-03, or 1925-03-01')
			.click(function(e) {

				if($(this).val() == 'Ex. 1925, 1925-03, or 1925-03-01') {

				    $(this).val('');
				}
			    });
		    }
		});
	}
    };

})(jQuery, Drupal);
