It must be guarantee that the `json_value` object contains exact
value type inside `m_data` field as it set in `m_value_type`.
So when value is created or it's content has been modified,
the field `m_value_type` must be synchronized with the `m_data`
content. On other hand, the `m_data` field must be always valid
pointer to the respective data value. If it is deleted some way,
the pointer must be set to `nullptr` and `m_value_type` must be
set to `t_null`. That's The Rule!