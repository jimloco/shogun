/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Fernando José Iglesias García
 * Copyright (C) 2012 Fernando José Iglesias García
 */

#include <shogun/labels/StructuredLabels.h>

using namespace shogun;

CStructuredLabels::CStructuredLabels()
: CLabels()
{
	init();
}

CStructuredLabels::CStructuredLabels(int32_t num_labels)
: CLabels()
{
	init();
	m_labels = new CDynamicObjectArray(num_labels);
	SG_REF(m_labels);
}

CStructuredLabels::~CStructuredLabels()
{
	SG_UNREF(m_labels);
}

CStructuredLabels* CStructuredLabels::obtain_from_generic(CLabels* base_labels)
{
	if ( base_labels->get_label_type() == LT_STRUCTURED )
		return (CStructuredLabels*) base_labels;
	else
		SG_SERROR("base_labels must be of dynamic type CStructuredLabels\n");

	return NULL;
}

void CStructuredLabels::ensure_valid(const char* context)
{
	if ( m_labels == NULL )
		SG_ERROR("Non-valid StructuredLabels in %s", context);
}

CDynamicObjectArray* CStructuredLabels::get_labels() const
{
	SG_REF(m_labels);
	return m_labels;
}

CStructuredData* CStructuredLabels::get_label(int32_t idx)
{
	ensure_valid("CStructuredLabels::get_label(int32_t)");	
	if ( idx < 0 || idx >= get_num_labels() )
		SG_ERROR("Index must be inside [0, num_labels-1]\n");

	return (CStructuredData*) m_labels->get_element(idx);
}

void CStructuredLabels::add_label(CStructuredData* label)
{
	m_labels->push_back(label);
}

bool CStructuredLabels::set_label(int32_t idx, CStructuredData* label)
{
	int32_t real_idx = m_subset_stack->subset_idx_conversion(idx);

	if ( real_idx < get_num_labels() )
	{
		return m_labels->insert_element(label, real_idx);
	}
	else
	{
		return false;
	}
}

int32_t CStructuredLabels::get_num_labels()
{
	if ( m_labels == NULL )
		return 0;
	else
		return m_labels->get_num_elements();
}

void CStructuredLabels::init()
{
	SG_ADD((CSGObject**) &m_labels, "m_labels", "The labels", MS_NOT_AVAILABLE);

	m_labels = NULL;
}
