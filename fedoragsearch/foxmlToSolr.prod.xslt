<?xml version="1.0" encoding="UTF-8"?> 
<!-- $Id: foxmlToSolr.xslt $ -->
<xsl:stylesheet version="1.0"
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform"   
    		xmlns:exts="xalan://dk.defxws.fedoragsearch.server.GenericOperationsImpl"
    		exclude-result-prefixes="exts"
		xmlns:foxml="info:fedora/fedora-system:def/foxml#"
		xmlns:dc="http://purl.org/dc/elements/1.1/"
		xmlns:oai_dc="http://www.openarchives.org/OAI/2.0/oai_dc/"
		xmlns:mods="http://www.loc.gov/mods/v3"
		xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
		xmlns:fedora="info:fedora/fedora-system:def/relations-external#"
		xmlns:fedora-model="info:fedora/fedora-system:def/model#"
		xmlns:islandora="http://islandora.ca/ontology/relsext#">

	<!-- Datastream-specific XSL Stylesheets -->
	<!-- This must be disabled due to certain ACL issues involving samba -->
	<!-- <xsl:import href="datastreams/mods.xslt" /> -->

	<xsl:output method="xml" indent="yes" encoding="UTF-8"/>

<!--
	 This xslt stylesheet generates the Solr doc element consisting of field elements
     from a FOXML record. 
     You must specify the index field elements in solr's schema.xml file,
     including the uniqueKey element, which in this case is set to "PID".
     Options for tailoring:
       - generation of fields from other XML metadata streams than DC
       - generation of fields from other datastream types than XML
         - from datastream by ID, text fetched, if mimetype can be handled.
-->

	<xsl:param name="REPOSITORYNAME" select="repositoryName"/>
	<xsl:param name="FEDORASOAP" select="repositoryName"/>
	<xsl:param name="FEDORAUSER" select="repositoryName"/>
	<xsl:param name="FEDORAPASS" select="repositoryName"/>
	<xsl:param name="TRUSTSTOREPATH" select="repositoryName"/>
	<xsl:param name="TRUSTSTOREPASS" select="repositoryName"/>
	<xsl:variable name="PID" select="/foxml:digitalObject/@PID"/>

	<!-- This must be disabled due to certain ACL issues involving samba -->
	<!-- MODS -->
			
	<!-- titleInfo -->
	<xsl:template match="mods:mods/mods:titleInfo">
	  
	  <!-- Title (CDATA) -->
	  <field name="MODS.mods.titleInfo_s">
			    
	    <xsl:apply-templates select="mods:nonSort" />
	    <xsl:text> </xsl:text>
	    <xsl:apply-templates select="mods:title"/>
	  </field>
	  
	  <!-- Sorting Title -->
	  <xsl:for-each select="(mods:title)[1]">
	    <field name="MODS.mods.titleInfo.title_ss">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Sub-Title -->
	  <xsl:for-each select="mods:subTitle">
	    <field name="MODS.mods.titleInfo.subTitle_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Part Number -->
	  <xsl:for-each select="mods:partNumber">
	    <field name="MODS.mods.titleInfo.partNumber_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>    
	</xsl:template>
	
	<!-- name -->
	<xsl:template match="mods:mods/mods:name">
	  
	  <!-- displayForm -->
	  <xsl:for-each select="mods:displayForm">
	    <field name="MODS.mods.name.displayForm_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>    
	</xsl:template>
	
	<!-- originInfo -->
	<xsl:template match="mods:mods/mods:originInfo">
	  
	  <!-- placeTerm -->
	  <xsl:for-each select="mods:place/mods:placeTerm">
	    <field name="MODS.mods.originInfo.place.placeTerm_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Publisher -->
	  <xsl:for-each select="mods:publisher">
	    <field name="MODS.mods.originInfo.publisher_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>

	  <!-- Publisher (Sorting) -->
	  <xsl:for-each select="(mods:publisher)[1]">
	    <field name="MODS.mods.originInfo.publisher_ss">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	</xsl:template>
	
	<!-- relatedItem/part -->
	<xsl:template match="mods:mods/mods:relatedItem/mods:part">
	  
	  <!-- W3CDTF-encoded datestamp -->
	  <xsl:for-each select="mods:date[@encoding='w3cdtf']">
	    <field name="MODS.mods.relatedItem.part.date.w3cdtf_dt">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Approximate datestamp -->
	  <xsl:for-each select="mods:date[@qualifier='approximate']">
	    <field name="MODS.mods.relatedItem.part.date.approximate_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Textual Volume -->
	  <!-- Possibly anomalous -->
	  <xsl:for-each select="mods:text[@type='volume']">
	    <field name="MODS.mods.relatedItem.part.text.volume_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Numeric Volume -->
	  <xsl:for-each select="mods:detail[@type='volume']/mods:number">
	    <field name="MODS.mods.relatedItem.part.detail.volume.number_i">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Textual Issue -->
	  <!-- Possibly anomalous -->
	  <xsl:for-each select="mods:text[@type='issue']">
	    <field name="MODS.mods.relatedItem.part.text.issue_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Numeric Issue -->
	  <xsl:for-each select="mods:detail[@type='issue']/mods:number">
	    <field name="MODS.mods.relatedItem.part.detail.issue.number_i">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	</xsl:template>
	
	<!-- relatedItem -->
	<!-- <xsl:template match="mods:mods/mods:relatedItem"> -->
	<xsl:template name="relatedItem" match="mods:mods/mods:relatedItem">

	  <!-- part -->
	  <xsl:apply-templates select="mods:part" />
	  
	  <!-- title -->
	  <xsl:for-each select="mods:titleInfo/mods:title">
	    <field name="MODS.mods.relatedItem.titleInfo.title_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Alternative datestamp -->
	  <xsl:for-each select="mods:originInfo/mods:dateIssued[@encoding='w3cdtf']">
	    <field name="MODS.mods.relatedItem.originInfo.dateIssued.w3cdtf_dt">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	  
	  <!-- Alternative approximate datestamp -->
	  <xsl:for-each select="mods:originInfo/mods:dateIssued[@qualifier='approximate']">
	    <field name="MODS.mods.relatedItem.originInfo.dateIssued.approximate_s">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>
	</xsl:template>

	<!-- relatedItem (Sorting) -->
	<xsl:template match="mods:mods/mods:relatedItem[1]">

	  <!-- title -->
	  <xsl:for-each select="mods:titleInfo/mods:title[1]">
	    <field name="MODS.mods.relatedItem.titleInfo.title_ss">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>

	  <!-- date -->
	  <xsl:for-each select="mods:originInfo/mods:dateIssued[@encoding='w3cdtf'] | mods:part/mods:date[@encoding='w3cdtf']">
	    <field name="MODS.mods.relatedItem.date.w3cdtf_dts">
	      
	      <xsl:apply-templates />
	    </field>
	  </xsl:for-each>

	  <xsl:call-template name="relatedItem" />
	</xsl:template>

	<!-- identifier -->
	<xsl:template match="mods:identifier">
	  <field name="MODS.mods.identifier.local_is">
	      
	    <xsl:apply-templates />
	  </field>
	</xsl:template>

	<!-- Notes -->
	<!-- Administrative notes -->
	<xsl:template name="note-admin" match="mods:note[@type='admin']">

	  <field name="MODS.mods.note.admin_s">

	    <xsl:apply-templates />
	  </field>
	</xsl:template>

	<xsl:template match="mods:note[@type='admin'][1]">

	  <field name="MODS.mods.note.admin_ss">

	    <xsl:apply-templates />
	  </field>
	  <xsl:call-template name="note-admin" />
	</xsl:template>

	<!-- MODS Document -->
	<xsl:template match="mods:mods">
	  
	  <xsl:apply-templates select="mods:titleInfo" />
	  <xsl:apply-templates select="mods:name" />
	  <xsl:apply-templates select="mods:place" />
	  <xsl:apply-templates select="mods:originInfo" />
	  <xsl:apply-templates select="mods:relatedItem" />
	  <xsl:apply-templates select="mods:identifier" />
	  <xsl:apply-templates select="mods:note" />
	</xsl:template>

	<xsl:template match="/">
		<!-- The following allows only active FedoraObjects to be indexed. -->
		<xsl:if test="foxml:digitalObject/foxml:objectProperties/foxml:property[@NAME='info:fedora/fedora-system:def/model#state' and @VALUE='Active']">
			<xsl:if test="not(foxml:digitalObject/foxml:datastream[@ID='METHODMAP'] or foxml:digitalObject/foxml:datastream[@ID='DS-COMPOSITE-MODEL'])">
				<xsl:if test="starts-with($PID,'')">
					<xsl:apply-templates mode="activeFedoraObject"/>
				</xsl:if>
			</xsl:if>
		</xsl:if>
		<!-- The following allows inactive FedoraObjects to be deleted from the index. -->
		<xsl:if test="foxml:digitalObject/foxml:objectProperties/foxml:property[@NAME='info:fedora/fedora-system:def/model#state' and @VALUE='Inactive']">
			<xsl:if test="not(foxml:digitalObject/foxml:datastream[@ID='METHODMAP'] or foxml:digitalObject/foxml:datastream[@ID='DS-COMPOSITE-MODEL'])">
				<xsl:if test="starts-with($PID,'')">
					<xsl:apply-templates mode="inactiveFedoraObject"/>
				</xsl:if>
			</xsl:if>
		</xsl:if>
	</xsl:template>

	<xsl:template match="/foxml:digitalObject" mode="activeFedoraObject">
		<add> 
		<doc> 
			<field name="PID">
				<xsl:value-of select="$PID"/>
			</field>
			<field name="REPOSITORYNAME">
				<xsl:value-of select="$REPOSITORYNAME"/>
			</field>
			<field name="REPOSBASEURL">
				<xsl:value-of select="substring($FEDORASOAP, 1, string-length($FEDORASOAP)-9)"/>
			</field>
			<xsl:for-each select="foxml:objectProperties/foxml:property">
				<field>
					<xsl:attribute name="name"> 
						<xsl:value-of select="concat('fgs.', substring-after(@NAME,'#'))"/>
					</xsl:attribute>
					<xsl:value-of select="@VALUE"/>
				</field>
			</xsl:for-each>

			<!-- RELS-EXT -->
			<!-- fedora-model:hasModel -->
			<xsl:for-each select="foxml:datastream[@ID='RELS-EXT']/foxml:datastreamVersion[last()]/foxml:xmlContent/rdf:RDF/rdf:Description/fedora-model:hasModel/@rdf:resource">
			  <field name="fgs.hasModel">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- fedora:isMemberOfCollection -->
			<xsl:for-each select="foxml:datastream[@ID='RELS-EXT']/foxml:datastreamVersion[last()]/foxml:xmlContent/rdf:RDF/rdf:Description/fedora:isMemberOfCollection/@rdf:resource">
			  <field name="fgs.isMemberOfCollection">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- fedora:isMemberOf -->
			<xsl:for-each select="foxml:datastream[@ID='RELS-EXT']/foxml:datastreamVersion[last()]/foxml:xmlContent/rdf:RDF/rdf:Description/fedora:isMemberOf/@rdf:resource">
			  <field name="fgs.isMemberOf">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- islandora:isPageOf -->
			<xsl:for-each select="foxml:datastream[@ID='RELS-EXT']/foxml:datastreamVersion[last()]/foxml:xmlContent/rdf:RDF/rdf:Description/islandora:isPageOf/@rdf:resource">
			  <field name="fgs.isPageOf">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Inline XML Datastream Content -->
			<!-- The MODS Datastream -->
			<xsl:for-each select="foxml:datastream[@ID='MODS']/foxml:datastreamVersion[last()]/foxml:xmlContent">

			  <xsl:apply-templates select="mods:mods" />
			</xsl:for-each>

			<!-- eastasia.Title.* -->
			<xsl:for-each select="foxml:datastream[@ID='MODS']/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:titleInfo/mods:title">

			  <xsl:choose>
			    <!-- eastasia.Title.Chinese -->
			    <xsl:when test="@xml:lang = 'zh'">
			      <field name="eastasia.Title.Chinese">

				<xsl:apply-templates />
			      </field>
			    </xsl:when>

			    <!-- eastasia.Title.Japanese -->
			    <xsl:when test="@xml:lang = 'Jpan'">

			      <field name="eastasia.Title.Japanese">

				<xsl:apply-templates />
			      </field>
			    </xsl:when>

			    <!-- eastasia.Title.Korean -->
			    <xsl:when test="@xml:lang = 'Kore'">

			      <field name="eastasia.Title.Korean">
				
				<xsl:apply-templates />
			      </field>
			    </xsl:when>
			  </xsl:choose>
			</xsl:for-each>

			<!-- eastasia.Subject.OCM -->
			<xsl:for-each select="foxml:datastream[@ID='MODS']/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[@authorityURI='http://www.yale.edu/hraf/outline.htm']/mods:topic">
			  <field name="eastasia.Subject.OCM">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

                        <!-- Sorting eastasia.Subject.OCM.sort -->
                        <xsl:for-each select="foxml:datastream[@ID='MODS']/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[@authorityURI='http://www.yale.edu/hraf/outline.htm'][1]/mods:topic">
			  <field name="eastasia.Subject.OCM.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

                        <!-- Sorting eastasia.Coverage.Location.Country.sort -->
			<xsl:for-each select="(foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject/mods:hierarchicalGeographic/mods:country)[1]">

			  <field name="eastasia.Coverage.Location.Country.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

                        <!-- Sorting eastasia.Creator.Maker.sort -->
			<xsl:for-each select="(foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name)[1]">

			  <xsl:choose>

			    <!-- Creator.Maker -->
			    <xsl:when test="mods:role/mods:roleTerm[text() = 'pht']">
			      <field name="eastasia.Creator.Maker.sort">
				
				<xsl:apply-templates select="mods:namePart" />
			      </field>
			    </xsl:when>
			  </xsl:choose>
			</xsl:for-each>

			<!-- Dates -->
			<!-- Image dates -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCreated[@point='start']">
			  <field name="eastasia.Date.Image.Lower">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCreated[@point='end']">
			  <field name="eastasia.Date.Image.Upper">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			
			<!-- Artifact dates -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateIssued[@point='start']">
			  <field name="eastasia.Date.Artifact.Lower">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateIssued[@point='end']">
			  <field name="eastasia.Date.Artifact.Upper">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Misc. date field -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='original']">
			  <field name="eastasia.Date.Original">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='search']">
			  <field name="eastasia.Date.Search">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Description.Ethnicity -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='ethnicity']">
			  <field name="eastasia.Description.Ethnicity">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Coverage.Location.Country -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject/mods:hierarchicalGeographic/mods:country">
			  <field name="eastasia.Coverage.Location.Country">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Coverage.Location -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject/mods:geographic">
			  <field name="eastasia.Coverage.Location">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Format.Medium -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:physicalDescription/mods:form">
			  <field name="eastasia.Format.Medium">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Description.Indicia -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='indicia']">
			  <field name="eastasia.Description.Indicia">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Contributor.Donor -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='acquisition']">
			  <field name="eastasia.Contributor.Donor">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- MODS <name> elements -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name">

			  <xsl:choose>

			    <!-- Creator.Maker -->
			    <xsl:when test="mods:role/mods:roleTerm[text() = 'pht']">
			      <field name="eastasia.Creator.Maker">
				
				<xsl:apply-templates select="mods:namePart" />
			      </field>
			    </xsl:when>

			    <!-- Contributors.Digital -->
			    <xsl:when test="mods:role/mods:roleTerm[text() = 'ctb']">
			      <field name="eastasia.Contributors.Digital">
				
				<xsl:apply-templates select="mods:namePart" />
			      </field>
			    </xsl:when>
			  </xsl:choose>
			</xsl:for-each>

			<!-- Creator.Company -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:publisher">
			  <field name="eastasia.Creator.Company">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Relation.IsPartOf -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='admin']">
			  <field name="cdm.Relation.IsPartOf">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!--
<field name="cdm.Relation.IsPartOf.sort" type="string" indexed="true" stored="true" multiValued="false"/>
-->
			<!-- Sorting -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='admin'][last()]">
			  <field name="cdm.Relation.IsPartOf.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!--
			   @author griffinj
			   LDR Fields
			  -->
<!--
   <field name="ldr.dc.contributor.author.sort" type="string" indexed="true" stored="true" multiValued="false"/>
   <field name="ldr.dc.contributor.editor.sort" type="string" indexed="true" stored="true" multiValued="false"/>
   <field name="ldr.dc.date.issued.sort" type="date" indexed="true" stored="true" multiValued="false"/>
   <field name="ldr.dc.identifier.citation.sort" type="string" indexed="true" stored="true" multiValued="false"/>
-->
			<!-- dc.contributor.author.sort -->
			<xsl:if test="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name[@type='personal'][1]/mods:role/mods:roleTerm[text()='aut']/../../mods:namePart/text()">
			  <field name="ldr.dc.contributor.author.sort">

			    <xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name[@type='personal']/mods:role/mods:roleTerm[text()='aut']/../../mods:namePart">
			      <xsl:value-of select="text()" />

			      <!-- Refactor -->
			      <!-- For the surname/forename/additional name tuple -->
			      <xsl:if test="(not(preceding-sibling::mods:namePart) or @type='family') and following-sibling::mods:namePart">

				<xsl:text>,</xsl:text>
			      </xsl:if>

			      <!-- For all additional names -->
			      <xsl:if test="following-sibling::mods:namePart">

				<xsl:text> </xsl:text>
			      </xsl:if>
			    </xsl:for-each>
			  </field>
			</xsl:if>

			<!-- dc.date.issued.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCaptured[1]">
			  <field name="ldr.dc.date.issued.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.identifier.citation.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='citation/reference'][1]">
			  <field name="ldr.dc.identifier.citation.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.contributor.author -->
			<xsl:if test="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name[@type='personal']/mods:role/mods:roleTerm[text()='aut']/../../mods:namePart/text()">
			  <field name="ldr.dc.contributor.author">

			    <xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name[@type='personal']/mods:role/mods:roleTerm[text()='aut']/../../mods:namePart">
			      <xsl:value-of select="text()" />

			      <!-- Refactor -->
			      <!-- For the surname/forename/additional name tuple -->
			      <xsl:if test="(not(preceding-sibling::mods:namePart) or @type='family') and following-sibling::mods:namePart">

				<xsl:text>,</xsl:text>
			      </xsl:if>

			      <!-- For all additional names -->
			      <xsl:if test="following-sibling::mods:namePart">

				<xsl:text> </xsl:text>
			      </xsl:if>
			    </xsl:for-each>
			  </field>
			</xsl:if>

			<!-- dc.contributor.other -->
			<xsl:if test="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name[@type='personal']/mods:role/mods:roleTerm[text()='oth']/../../mods:namePart/text()">
			  <field name="ldr.dc.contributor.other">

			    <xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name[@type='personal']/mods:role/mods:roleTerm[text()='oth']/../../mods:namePart">
			      <!-- Refactor -->
			      <!-- For the surname/forename/additional name tuple -->
			      <xsl:if test="(not(preceding-sibling::mods:namePart) or @type='family') and following-sibling::mods:namePart">

				<xsl:text>,</xsl:text>
			      </xsl:if>

			      <!-- For all additional names -->
			      <xsl:if test="following-sibling::mods:namePart">

				<xsl:text> </xsl:text>
			      </xsl:if>
			    </xsl:for-each>
			  </field>
			</xsl:if>

			<!-- dc.date.accessioned -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCaptured">

			  <field name="ldr.dc.date.accessioned">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.date.available -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateIssued">
			  <field name="ldr.dc.date.available">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.date.issued -->
			<!-- Mapped to dc.date.accessioned -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCaptured">
			  <field name="ldr.dc.date.issued">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.identifier.citation -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='citation/reference']">
			  <field name="ldr.dc.identifier.citation">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.identifier.uri -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:identifier[@type='uri']">
			  <field name="ldr.dc.identifier.uri">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.identifier.doi -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:identifier[@type='doi']">

			  <field name="ldr.dc.identifier.doi">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.identifier.issn -->
 			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:identifier[@type='issn']">
			  <field name="ldr.dc.identifier.issn">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.identifier.isbn -->
 			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:identifier[@type='isbn']">
			  <field name="ldr.dc.identifier.isbn">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.description.abstract -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:abstract">
			  <field name="ldr.dc.description.abstract">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.description.uri -->
			<!-- Mapped to dc.identifier.doi -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:identifier[@type='doi']">
			  <field name="ldr.dc.description.uri">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- dc.relation.ispartofseries -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:relatedItem[@type='isReferencedBy']/mods:titleInfo/mods:title">

			  <field name="ldr.dc.relation.ispartofseries">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!--
			   Fields for the Marquis de Lafayette Prints Collection
			  -->

<!--
   <field name="mdl_prints.description.series.sort" type="string" indexed="true" stored="true" multiValued="false" />
   <field name="mdl_prints.creator.sort" type="string" indexed="true" stored="true" multiValued="false" />
   <field name="mdl_prints.subject.lcsh.sort" type="string" indexed="true" stored="true" multiValued="false" />
   <field name="mdl_prints.format.medium.sort" type="string" indexed="true" stored="true" multiValued="false" />

   <field name="mdl_prints.date.original.sort" type="date" indexed="true" stored="true" multiValued="false" />

-->
			<!--   -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name[1]">

			  <xsl:choose>

			    <!-- mdl_prints.creator.sort -->
			    <xsl:when test="mods:role/mods:roleTerm[text() = 'cre']">
			      <field name="mdl_prints.creator.sort">
				
				<xsl:apply-templates select="mods:namePart" />
			      </field>
			    </xsl:when>
			  </xsl:choose>
			</xsl:for-each>
			<!-- mdl_prints.subject.lcsh.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[@authority='lcsh'][1]/mods:topic">
			  <field name="mdl_prints.subject.lcsh.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- mdl_prints.format.medium.sort -->
			<xsl:for-each select="(foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:physicalDescription/mods:form)[1]">
			  <field name="mdl_prints.format.medium.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- mdl_prints.description.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='series'][1]">

			  <field name="mdl_prints.description.series.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- mdl_prints.date.original.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCreated[1]">
			  <field name="mdl_prints.date.original.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- MODS <name> elements -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:name">

			  <xsl:choose>

			    <!-- mdl_prints.creator -->
			    <xsl:when test="mods:role/mods:roleTerm[text() = 'cre']">
			      <field name="mdl_prints.creator">
				
				<xsl:apply-templates select="mods:namePart" />
			      </field>
			    </xsl:when>
			  </xsl:choose>
			</xsl:for-each>
			
			<!-- mdl_prints.subject.lcsh -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[@authority='lcsh']/mods:topic">
			  <field name="mdl_prints.subject.lcsh">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.format.medium -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:physicalDescription/mods:form">
			  <field name="mdl_prints.format.medium">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.description -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:abstract">
			  <field name="mdl_prints.description">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.description.provenance -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='ownership']">
			  <field name="mdl_prints.description.provenance">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!--
			   mdl_prints.description.series
			   
			   Used for browsing and discovery
			   -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='series']">

			  <field name="mdl_prints.description.series">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.identifier.itemnumber -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:identifier[@type='item-number']">
			  <field name="mdl_prints.identifier.itemnumber">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.rights.digital -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:accessCondition">
			  <field name="mdl_prints.rights.digital">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.publisher.original -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:publisher">
			  <field name="mdl_prints.publisher.original">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.publisher.digital -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='statement of responsibility']">
			  <field name="mdl_prints.publisher.digital">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.format.digital -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='digital format']">
			  <field name="mdl_prints.format.digital">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.date.original -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCreated">
			  <field name="mdl_prints.date.original">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.format.extent -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:physicalDescription/mods:extent">
			  <field name="mdl_prints.format.extent">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mdl_prints.source -->
			<!-- Resolves DSS-348 -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:location/mods:physicalLocation">
			  <field name="mdl_prints.source">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!--
			   Fields for the Geology Slides Collection:
			   
			   description.critical
			   description.geologic.feature
			   description.geologic.process
			   coverage.location.country
			   coverage.location.state
			   description.location
			   date.display
			   date.search
			  -->

			<!-- geology_slides.description.critical -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='content']">
			  <field name="geology_slides.description.critical">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides.description.geologic.feature -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[@authority='metadb-geology-geologic-feature']/mods:topic">
			  <field name="geology_slides.description.geologic.feature">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides.description.geologic.process -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[@authority='metadb-geology-geologic-process']/mods:topic">
			  <field name="geology_slides.description.geologic.process">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides.coverage.location.country -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject/mods:hierarchicalGeographic/mods:country">
			  <field name="geology_slides.coverage.location.country">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides.coverage.location.state -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject/mods:hierarchicalGeographic/mods:state">
			  <field name="geology_slides.coverage.location.state">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides.date.display -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='display']">
			  <field name="geology_slides.date.display">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides.date.search -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='search']">
			  <field name="geology_slides.date.search">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!--
			   Fields for the Geology Slides ESI Collection:
			   
			   subject
			   description.vantagepoint
			   date.original
			   description
			   coverage.location
			   relation.seealso.image
			   relation.seealso.book
			   identifier.dmrecord
			  -->

<!--
   <field name="geology_slides_esi.subject.sort" type="string" indexed="true" stored="true" multiValued="false" />
   <field name="geology_slides_esi.date.original.sort" type="date" indexed="true" stored="true" multiValued="false" />
   <field name="geology_slides_esi.coverage.location.sort" type="string" indexed="true" stored="true" multiValued="false" />
-->

			<!-- geology_slides_esi.subject.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[1]/mods:topic[1]">
			  <field name="geology_slides_esi.subject.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- geology_slides_esi.date.original.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='original'][1]">
			  <field name="geology_slides_esi.date.original.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- geology_slides_esi.coverage.location.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject[1]/mods:geographic">
			  <field name="geology_slides_esi.coverage.location.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Remove ? -->
			<!-- geology_slides_esi.subject -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject/mods:topic">
			  <field name="geology_slides_esi.subject">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides_esi.description.vantagepoint -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='vantagepoint']">
			  <field name="geology_slides_esi.description.vantagepoint">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides_esi.date.original -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='original']">
			  <field name="geology_slides_esi.date.original">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Remove ?-->
			<!-- geology_slides_esi.description -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:abstract">
			  <field name="geology_slides_esi.description">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides_esi.coverage.location -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:subject/mods:geographic">
			  <field name="geology_slides_esi.coverage.location">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides_esi.relation.seealso.image -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:relatedItem[@type='original']/mods:note[@type='citation']">
			  <field name="geology_slides_esi.relation.seealso.image">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides_esi.relation.seealso.book -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:relatedItem[@type='host']/mods:note[@type='citation']">
			  <field name="geology_slides_esi.relation.seealso.book">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- geology_slides_esi.relation.identifier.dmrecord -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:identifier[@type='lafayette-cdm']">
			  <field name="geology_slides_esi.identifier.dmrecord">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- McKelvy House Collection -->

			<!-- mckelvy.data.original.display.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='display'][1]">
			  <field name="mckelvy.date.original.display.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- mckelvy.data.original.display -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='display']">
			  <field name="mckelvy.date.original.display">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mckelvy.data.original.search -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='search']">
			  <field name="mckelvy.date.original.search">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mckelvy.description.note -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='description']">
			  <field name="mckelvy.description.note">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- mckelvy.source -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:place/mods:placeTerm">
			  <field name="mckelvy.source">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- War Casualties -->
<!--
   <field name="war_casualties.description.class.sort" type="string" indexed="true" stored="true" multiValued="false" />
   <field name="war_casualties.description.military.branch.sort" type="string" indexed="true" stored="true" multiValued="false" />
   <field name="war_casualties.description.military.unit.sort" type="string" indexed="true" stored="true" multiValued="false" />
-->
			<!-- war_casualties.description.class.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='lafayette-class'][1]">
			  <field name="war_casualties.description.class.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- war_casualties.description.military.branch.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='military-branch'][1]">
			  <field name="war_casualties.description.military.branch.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<!-- war_casualties.contributor.military.unit.sort -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='military-unit'][1]">
			  <field name="war_casualties.contributor.military.unit.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

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

			<!-- war_casualties.date.birth.display -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='birth-display']">
			  <field name="war_casualties.date.birth.display">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.coverage.place.birth -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:note[@type='place-birth']">
			  <field name="war_casualties.coverage.place.birth">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- war_casualties.date.death.display -->
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateOther[@type='death-display']">
			  <field name="war_casualties.date.death.display">

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

			
			<!-- Historical Photograph Collection -->
			<!-- Dates -->
			<!-- Image dates -->
<!--
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCreated[@point='start']">
			  <field name="eastasia.Date.Image.Lower">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/mods:mods/mods:originInfo/mods:dateCreated[@point='end']">
			  <field name="eastasia.Date.Image.Upper">
			    
			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
-->

<!--

   <field name="dc.subject.sort" type="string" indexed="true" stored="true" multiValue="false"/>
   <field name="dc.date.sort" type="date" indexed="true" stored="true" multiValue="false"/>
   <field name="dc.type.sort" type="string" indexed="true" stored="true" multiValue="false"/>
   <field name="dc.publisher.sort" type="string" indexed="true" stored="true" multiValue="false"/>
   <field name="dc.coverage.sort" type="string" indexed="true" stored="true" multiValue="false"/>
-->




			<!-- Dublin Core (Fedora Commons) fields indexed for sorting -->

			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/oai_dc:dc/dc:subject[1]">
			  <field name="dc.subject.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/oai_dc:dc/dc:date[1]">
			  <field name="dc.date.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/oai_dc:dc/dc:type[1]">
			  <field name="dc.type.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/oai_dc:dc/dc:publisher[1]">
			  <field name="dc.publisher.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>
			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/oai_dc:dc/dc:coverage[1]">
			  <field name="dc.coverage.sort">

			    <xsl:apply-templates />
			  </field>
			</xsl:for-each>

			<!-- Indexing all Dublin Core fields -->

			<xsl:for-each select="foxml:datastream/foxml:datastreamVersion[last()]/foxml:xmlContent/oai_dc:dc/*">
			  <field>
			    <xsl:attribute name="name">
			      <xsl:value-of select="concat('dc.', substring-after(name(),':'))"/>
			    </xsl:attribute>
			    <xsl:value-of select="text()"/>
			  </field>
			</xsl:for-each>

			<!-- a datastream is fetched, if its mimetype 
			     can be handled, the text becomes the value of the field.
			     This is the version using PDFBox,
			     below is the new version using Apache Tika. -->
			<!-- 
			<xsl:for-each select="foxml:datastream[@CONTROL_GROUP='M' or @CONTROL_GROUP='E' or @CONTROL_GROUP='R']">
				<field>
					<xsl:attribute name="name">
						<xsl:value-of select="concat('ds.', @ID)"/>
					</xsl:attribute>
					<xsl:value-of select="exts:getDatastreamText($PID, $REPOSITORYNAME, @ID, $FEDORASOAP, $FEDORAUSER, $FEDORAPASS, $TRUSTSTOREPATH, $TRUSTSTOREPASS)"/>
				</field>
			</xsl:for-each>
			 -->

			<!-- Text and metadata extraction using Apache Tika. 
				Parameters for getDatastreamFromTika, getDatastreamTextFromTika, and getDatastreamMetadataFromTika:
				- indexFieldTagName		: either "IndexField" (with the Lucene plugin) or "field" (with the Solr plugin)
				- textIndexField		: fieldSpec for the text index field, null or empty if not to be generated								 (not used with getDatastreamMetadataFromTika)
				- indexfieldnamePrefix	: optional or empty, prefixed to the metadata indexfield names											 (not used with getDatastreamTextFromTika)
				- selectedFields		: comma-separated list of metadata fieldSpecs, if empty then all fields are included with default params (not used with getDatastreamTextFromTika)
				- fieldSpec				: metadataFieldName ['=' indexFieldName] ['/' [index] ['/' [store] ['/' [termVector] ['/' [boost]]]]]
						metadataFieldName must be exactly as extracted by Tika from the document. 
										  You may see the available names if you log in debug mode, 
										  look for "METADATA name=" under "fullDsId=" in the log, when "getFromTika" was called during updateIndex
						indexFieldName is used as the generated index field name,
										  if not given, GSearch uses metadataFieldName after replacement of the characters ' ', ':', '/', '=', '(', ')' with '_'
						the following parameters are used with Lucene (with Solr these values are specified in schema.xml)
						index			: ['TOKENIZED'|'UN_TOKENIZED']	# first alternative is default
						store			: ['YES'|'NO']					# first alternative is default
						termVector		: ['YES'|'NO']					# first alternative is default
						boost			: <decimal number>				# '1.0' is default
			-->
			<xsl:for-each select="foxml:datastream[@CONTROL_GROUP='M' or @CONTROL_GROUP='E' or @CONTROL_GROUP='R']">
			  <xsl:value-of disable-output-escaping="yes" select="exts:getDatastreamFromTika($PID, $REPOSITORYNAME, @ID, 'field', concat('ds.', @ID), concat('dsmd_', @ID, '.'), '', $FEDORASOAP, $FEDORAUSER, $FEDORAPASS, $TRUSTSTOREPATH, $TRUSTSTOREPASS)"/>
			</xsl:for-each>

			<!-- 
			creating an index field with all text from the foxml record and its datastreams
			-->

			<field name="foxml.all.text">
			  <xsl:for-each select="//text()">
			    <xsl:value-of select="."/>
			    <xsl:text>&#160;</xsl:text>
			  </xsl:for-each>
			  <!--<xsl:for-each select="//foxml:datastream[@CONTROL_GROUP='M' or @CONTROL_GROUP='E' or @CONTROL_GROUP='R']">-->

			  <xsl:for-each select="//foxml:datastream">
			      <xsl:value-of select="exts:getDatastreamText($PID, $REPOSITORYNAME, @ID, $FEDORASOAP, $FEDORAUSER, $FEDORAPASS, $TRUSTSTOREPATH, $TRUSTSTOREPASS)"/>
			      <xsl:text>&#160;</xsl:text>
			  </xsl:for-each>
			  <!--</xsl:for-each>-->
			</field>
		</doc>
		</add>
	</xsl:template>

	<xsl:template match="/foxml:digitalObject" mode="inactiveFedoraObject">
		<delete> 
			<id><xsl:value-of select="$PID"/></id>
		</delete>
	</xsl:template>
	
</xsl:stylesheet>
