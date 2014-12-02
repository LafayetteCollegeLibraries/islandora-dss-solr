<?xml version="1.0" encoding="UTF-8"?> 

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

  <!-- MODS -->

  <!-- titleInfo -->
  <xsl:template match="mods:mods/mods:titleInfo">

    <!-- Title (CDATA) -->
    <field name="mods:mods/mods:titleInfo/*">

      <xsl:apply-templates select="mods:nonSort" />
      <xsl:text> </xsl:text>
      <xsl:apply-templates select="mods:title"/>
    </field>

    <!-- Title for sorting -->
    <xsl:for-each select="(mods:title)[1]">
      <field name="(mods:mods/mods:titleInfo/mods:title)[1]">
      
	<xsl:apply-templates />
      </field>
    </xsl:for-each>

    <!-- Sub-Title -->
    <xsl:for-each select="mods:subTitle">
      <field name="mods:mods/mods:titleInfo/mods:subTitle">
      
	<xsl:apply-templates />
      </field>
    </xsl:for-each>

    <!-- Part Number -->
    <xsl:for-each select="mods:partNumber">
      <field name="mods:mods/mods:titleInfo/mods:partNumber">
      
	<xsl:apply-templates />
      </field>
    </xsl:for-each>    
  </xsl:template>

  <!-- name -->
  <xsl:template match="mods:mods/mods:name">

    <!-- displayForm -->
    <xsl:for-each select="mods:displayForm">
      <field name="mods:mods/mods:name/mods:displayForm">
	
	<xsl:apply-templates />
      </field>
    </xsl:for-each>    
  </xsl:template>

  <!-- place -->
  <xsl:template match="mods:mods/mods:place">

    <!-- placeTerm -->
    <xsl:for-each select="mods:placeTerm">
      <field name="mods:mods/mods:originInfo/mods:place/mods:placeTerm">
      
	<xsl:apply-templates />
      </field>
    </xsl:for-each>
  </xsl:template>

  <!-- originInfo -->
  <xsl:template match="mods:mods/mods:originInfo">

    <!-- Publisher -->
    <xsl:for-each select="mods:publisher">
      <field name="mods:mods/originInfo/publisher">
      
	<xsl:apply-templates />
      </field>
    </xsl:for-each>
  </xsl:template>

  <!-- relatedItem/part -->
  <xsl:template match="mods:mods/mods:relatedItem/mods:part">

    <!-- W3CDTF-encoded datestamp -->
    <xsl:for-each select="mods:date[@encoding='w3cdtf']">
      <field name="mods:mods/relatedItem/part/date[@encoding='w3cdtf']">
      
      <xsl:apply-templates />
    </field>
  </xsl:for-each>

  <!-- Approximate datestamp -->
  <xsl:for-each select="mods:date[@qualifier='approximate']">
    <field name="mods:mods/relatedItem/part/date[@qualifier='approximate']">
      
      <xsl:apply-templates />
    </field>
  </xsl:for-each>

  <!-- Textual Volume -->
  <!-- Possibly anomalous -->
  <xsl:for-each select="mods:text[@type='volume']">
    <field name="mods:mods/relatedItem/part/text[@type='volume']">
      
      <xsl:apply-templates />
    </field>
  </xsl:for-each>

  <!-- Numeric Volume -->
  <xsl:for-each select="mods:detail[@type='volume']/mods:number">
    <field name="mods:mods/relatedItem/part/detail[@type='volume']/number">
      
      <xsl:apply-templates />
    </field>
  </xsl:for-each>

  <!-- Textual Issue -->
  <!-- Possibly anomalous -->
  <xsl:for-each select="mods:text[@type='issue']">
    <field name="mods:mods/relatedItem/part/text[@type='issue']">
      
      <xsl:apply-templates />
    </field>
  </xsl:for-each>

  <!-- Numeric Issue -->
  <xsl:for-each select="mods:detail[@type='issue']/mods:number">
    <field name="mods:mods/relatedItem/part/detail[@type='issue']/number">
      
      <xsl:apply-templates />
    </field>
  </xsl:for-each>
    
  </xsl:template>

  <!-- relatedItem -->
  <xsl:template match="mods:mods/mods:relatedItem">

    <!-- part -->
    <xsl:apply-templates select="mods:part" />

    <!-- title -->
    <xsl:for-each select="mods:titleInfo/mods:title">
      <field name="mods:mods/relatedItem/titleInfo/title">
      
	<xsl:apply-templates />
      </field>
    </xsl:for-each>

    <!-- Alternative datestamp -->
    <xsl:for-each select="mods:originInfo/mods:dateIssued[@encoding='w3cdtf']">
      <field name="mods:mods/relatedItem/originInfo/dateIssued[@encoding='w3cdtf']">
      
	<xsl:apply-templates />
      </field>
    </xsl:for-each>

  </xsl:template>

  <!-- MODS Document -->
  <xsl:template match="mods:mods">

    <xsl:apply-templates select="mods:titleInfo" />
    <xsl:apply-templates select="mods:name" />
    <xsl:apply-templates select="mods:place" />
    <xsl:apply-templates select="mods:originInfo" />
    <xsl:apply-templates select="mods:relatedItem" />
  </xsl:template>

</xsl:stylesheet>
