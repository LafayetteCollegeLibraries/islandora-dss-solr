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

	    $('.islandora-solr-search-field option').click(function(e) {

		    if($(this).val() == 'dc.date') {

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
