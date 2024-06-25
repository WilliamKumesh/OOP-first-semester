#include"htable.h"
#include <stdlib.h>
#include <string.h>

static const size_t default_size = 4;
static const float resize_const = 0.7;

enum state
{
    USED = -1, NOT_USED = 0, USING = 1
};

typedef struct NewHTableItem
{
    HTableItem item;
    bool wasUsed;
}
NewHTableItem;

typedef struct HTable
{
    NewHTableItem* items;
    size_t capacity;
    size_t count_and_deleted;
    size_t count;
    size_t keySize, valueSize;
    size_t(*hash_func)(const void*);
    bool (*equals_func)(const void*, const void*);

}HTable;

static enum state check_state(NewHTableItem item)
{
    if (item.item.key == NULL)
    {
        return item.wasUsed ? USED : NOT_USED;
    }

	return USING;
    
}

static void init_item(const void* htable, size_t index, enum state item_state, const void* key, void* value)
{
    HTable* table = htable;

    table->items[index].item.key = key;
    table->items[index].item.value = value;
    table->items[index].wasUsed = true;
    table->count++;
    if (item_state == NOT_USED)
    {
        table->count_and_deleted++;
    }
}

static void init_table(const void* htable, size_t keySize, size_t valueSize, size_t hash(const void*), bool(*equals)(const void*))
{
    HTable* table = htable;

    table->items = NULL;
    table->count = 0;
    table->capacity = 0;
    table->count_and_deleted = 0;
    table->keySize = keySize;
    table->valueSize = valueSize;
    table->hash_func = hash;
    table->equals_func = equals;
}

static size_t find_index(const void* htable, const void* key)
{
    const HTable* table = htable;

    if (table->capacity == 0 || htable == NULL)
    {
        return htable_stop(htable);
    }

    size_t ins_index = htable_stop(htable);
    bool flag_first_to_ins = false;

    size_t index = table->hash_func(key) % table->capacity;

    if(index == htable_stop(htable))
    {
        return htable_stop(htable);
    }

    enum state item_state = check_state(table->items[index]);

    if (item_state != USING)
    {
        flag_first_to_ins = true;
        ins_index =  index;
    }

    size_t i = 0;

    while (item_state != NOT_USED && i < table->capacity)
    {
        if (item_state == USING)
        {
            if (table->equals_func(table->items[index].item.key, key))
            {
                return index;
            }
        }
        i++;
        index = (index + 1) % table->capacity;

        if (index == htable_stop(htable))
        {
            return htable_stop(htable);
        }

        item_state = check_state(table->items[index]);

        if (item_state != USING && !flag_first_to_ins)
        {
            flag_first_to_ins = true;
            ins_index = index;
        }
    }

    return ins_index;
}

static void insert_in_clean_table(HTable* htable, const void* key, void* value)
{
    HTable* table = htable;

    const size_t index = find_index(htable, key);

    if (index != htable_stop(htable))
    {
        init_item(htable, index, check_state(table->items[index]), key, value);
    }
}

static void destroy_item(NewHTableItem* item, void(*destroy)(void*))
{
    if (item == NULL)
    {
        return;
    }

    if (destroy != NULL)
    {
        destroy(&item->item);
    }

    free(item->item.key);
    free(item->item.value);
    item->item.key = NULL;
    item->item.value = NULL;
}

static void rehash(void* htable, size_t capacity)
{
    HTable* table = htable;

    if(capacity == 0)
    {
        capacity = default_size;
    }

    NewHTableItem* items_n = calloc(capacity, sizeof(NewHTableItem));

    if (items_n == NULL)
    {
        return;
    }

    table->count_and_deleted = 0;
    table->count = 0;
    size_t prev_capacity = table->capacity;
    table->capacity = capacity;

    NewHTableItem* item = table->items;
    table->items = items_n;
    items_n = item;

    for (size_t i = 0; i < prev_capacity; i++)
    {
        if (check_state(items_n[i]) == USING)
        {
            insert_in_clean_table(htable, items_n[i].item.key, items_n[i].item.value);
        }
    }

    free(items_n);
}

void* htable_create(size_t keySize, size_t valueSize, size_t hash(const void*), bool(*equals)(const void*, const void*))
{
    if (keySize == 0 || valueSize == 0 || hash == NULL || equals == NULL)
    {
        return NULL;
    }

    HTable* htable = malloc(sizeof(HTable));

    if (htable == NULL)
    {
        return NULL;
    }

    init_table(htable, keySize, valueSize, hash, equals);

    return htable;
}

void htable_destroy(void* htable, void(*destroy)(void*))
{
    if(htable == NULL)
    {
        return;
    }
	const HTable* table = htable;

	htable_clear(htable, destroy);
	free(table->items);

    free(htable);
}

void* htable_init(void* htable, size_t keySize, size_t valueSize, size_t hash(const void*), 
    bool(*equals)(const void*, const void*), void(*destroy)(void*))
{
    if (htable == NULL || keySize == 0 || valueSize == 0 || hash == NULL || equals == NULL)
    {
        return NULL;
    }

    HTable* table = htable;

    htable_clear(table, destroy);
	free(table->items);

    init_table(htable, keySize, valueSize, hash, equals);

    return table;
}

void htable_clear(void* htable, void(*destroy)(void*))
{
    if (htable == NULL)
    {
        return;
    }

    HTable* table = htable;

    for (size_t i = 0; i < table->capacity; i++)
    {
        destroy_item(&table->items[i], destroy);
        table->items[i].wasUsed = false;
    }

    table->count = 0;
    table->count_and_deleted = 0;
}

size_t htable_count(const void* htable)
{
    if (htable == NULL)
    {
        return INVALID;
    }

    const HTable* table = htable;

    return table->count;
}

size_t htable_stop(const void* htable)
{
    return INVALID;
}

size_t htable_first(const void* htable)
{
    if (htable == NULL)
    {
        return htable_stop(htable);
    }

    const HTable* table = htable;

    for (size_t i = 0; i < table->capacity; i++)
    {
        if (check_state(table->items[i]) == USING)
        {
            return i;
        }
    }

    return htable_stop(htable);
}

void* htable_current(const void* htable, size_t item_id)
{
    if (htable == NULL)
    {
        return NULL;
    }

    const HTable* table = htable;

    if (item_id == htable_stop(htable) || item_id >= table->capacity || check_state(table->items[item_id]) != USING)
    {
        return NULL;
    }
    return &table->items[item_id].item;
}

size_t htable_last(const void* htable)
{
    if (htable == NULL)
    {
        return htable_stop(htable);
    }

    const HTable* table = htable;

    for(int i = (int)table->capacity - 1; i >= 0; i--)
    {
        if (check_state(table->items[i]) == USING)
        {
            return i;
        }
    }

    return htable_stop(htable);
}

size_t htable_next(const void* htable, size_t item_id)
{
    if (htable == NULL)
    {
        return htable_stop(htable);
    }

    const HTable* table = htable;

    if (item_id == htable_stop(htable) || item_id >= table->capacity || check_state(table->items[item_id]) != USING)
    {
        return htable_stop(htable);
    }
    
    for (size_t i = item_id + 1; i < table->capacity; i++)
    {
        if (check_state(table->items[i]) == USING)
        {
            return i;
        }
    }

    return htable_stop(htable);
}

size_t htable_prev(const void* htable, size_t item_id)
{
    if (htable == NULL)
    {
        return htable_stop(htable);
    }

    const HTable* table = htable;

    if (item_id >= table->capacity || item_id == htable_stop(htable) || check_state(table->items[item_id]) != USING)
    {
        return htable_stop(htable);
    }

    for (int i = (int)(item_id - 1); i >= 0; i--)
    {
        if (check_state(table->items[i]) == USING)
        {
            return i;
        }
    }
    return htable_stop(htable);
}

void* htable_item(const void* htable, const void* key)
{
    if (htable == NULL || key == NULL)
    {
        return NULL;
    }

    const HTable* table = htable;

    size_t index = find_index(htable, key);

    if (index != htable_stop(htable) && check_state(table->items[index]) == USING)
    {
        return table->items[index].item.value;
    }
    
    return NULL;
}

void htable_remove(void* htable, const void* key, void(*destroy)(void*))
{
    if (htable == NULL || key == NULL)
    {
        return;
    }

    HTable* table = htable;

    size_t index = find_index(htable, key);

    if (index != htable_stop(htable) && check_state(table->items[index]) == USING)
    {
        destroy_item(&table->items[index], destroy);
        table->count--;
    }
}

void htable_erase(void* htable, size_t item_id, void(*destroy)(void*))
{
    if (htable == NULL)
    {
        return;
    }

    HTable* table = htable;

    if (item_id == htable_stop(htable) || item_id >= table->capacity || check_state(table->items[item_id]) != USING)
    {
        return;
    }

    if (htable_current(htable, item_id) != NULL)
    {
        destroy_item(htable_current(htable, item_id), destroy);
        table->count--;
    }
}

void* htable_insert(void* htable, const void* key, bool* createFlag)
{
    if (htable == NULL || key == NULL || createFlag == NULL)
    {
        return NULL;
    }

    HTable* table = htable;

    if (table->count + 1 > resize_const * table->capacity)
    {
        rehash(htable, table->capacity*2);
    }
    
    if (table->count_and_deleted > 2 * table->count)
    {
        rehash(htable, table->capacity);
    }

    size_t index = find_index(htable, key);

    if (index == htable_stop(htable))
    {
	    *createFlag = false;
	    return NULL;
    }

    enum state index_state = check_state(table->items[index]);

    if (index_state == USING)
    {
	    *createFlag = false;
	    return table->items[index].item.value;
    }

    void* temp_key = malloc(table->keySize);
    void* temp_value = malloc(table->valueSize);

    if (temp_key == NULL || temp_value == NULL)
    {
        free(temp_key);
        free(temp_value);
        *createFlag = false;
	    return NULL;
    }

    init_item(htable, index, index_state, temp_key, temp_value);

    *createFlag = true;
    memcpy(table->items[index].item.key, key, table->keySize);
    return table->items[index].item.value;
}