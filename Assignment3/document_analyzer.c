#include "document_analyzer.h"

static char* s_buffer = NULL;

static const char** s_sentence;
static const char*** s_paragraph;
static const char**** s_document;

int load_document(const char* document)
{
    FILE* stream;
    long length;
    size_t word_count = 0;
    char* p;
    const char** pp;
    const char*** ppp;
    const char**** pppp;

    stream = fopen(document, "r");
    if (stream == NULL) {
        return FALSE;
    }

    fseek(stream, 0, SEEK_END);
    length = ftell(stream);
    fseek(stream, 0, SEEK_SET);

    s_buffer = malloc(length + 1);

    length = read_in(stream, &word_count);
    s_buffer[length] = '\0';

    fclose(stream);

/* make _tree */
    
    s_sentence = malloc((word_count + 1) * sizeof(char*));
    s_paragraph = malloc((word_count + 1) * sizeof(char*));
    s_document = malloc((word_count + 1) * sizeof(char*));

    if (length == 0) {
        return TRUE;
    }

    p = s_buffer;
    pp = s_sentence;
    ppp = s_paragraph;
    pppp = s_document;

    *pp = (const char*)p;
    *ppp = pp;
    *pppp = ppp;

    while (*p != '\0') {
        if (*p == ',' || *p == ' ') {
            if (*p == ',') {
                *p = '\0';
                ++p;
                continue;
            }
            *p = '\0';
            ++p;
            *(++pp) = (const char*)p;
        } else if (*p == '.' || *p == '?' || *p == '!') {
            *p = '\0';
            if (*(p + 1) == '\0') {
                break;
            } else if (*(p + 1) != '\n') {
                p += 2;
                *(++pp) = (const char*)p;
                *(++ppp) = pp;
            } else {
                ++p;
            }
        } else if (*p == '\n') {
            while (*p == '\n') {
                *p++ = '\0';
            }
            *(++pp) = (const char*)p;
            *(++ppp) = pp;
            *(++pppp) = ppp;
        } else {
            ++p;
        }
    }

    *(++pp) = NULL;
    *(++ppp) = NULL;
    *(++pppp) = NULL;

    return TRUE;
}
long read_in(FILE* stream, size_t* out_word_count)
{
    char c1;
    char c2;
    
    size_t blank_count = 0;
    long read_count = 0;

    char* p = s_buffer;

    c1 = fgetc(stream);
    while( c1!= EOF) {
        c2 = fgetc(stream);
        *p++ = c1;
        read_count++;

        if (c1 == ' ') {
            ++blank_count;
        } else if (c1 == '\n' && c2 != '\n') {
            ++blank_count;
        }
        c1 = c2;
    }

    *out_word_count = read_count == 0 ? 0 : blank_count + 1;

    return read_count;
}

void dispose(void)
{
    free(s_buffer);
    s_buffer = NULL;

    free(s_sentence);
    s_sentence = NULL;

    free(s_paragraph);
    s_sentence = NULL;

    free(s_document);
    s_sentence = NULL;
}

unsigned int get_total_word_count(void)
{
    size_t count = 0;
    const char** pp = s_sentence;

    if (s_buffer == NULL || *s_buffer == '\0') {
        return 0;
    }

    while (*pp++ != NULL) {
        count++;
    }

    return count;
}

unsigned int get_total_sentence_count(void)
{
    size_t count = 0;
    const char*** ppp = s_paragraph;

    if (s_buffer == NULL || *s_buffer == '\0') {
        return 0;
    }

    while (*ppp++ != NULL) {
        ++count;
    }

    return count;
}

unsigned int get_total_paragraph_count(void)
{
    size_t count = 0;
    const char**** pppp = s_document;
    
    if (s_buffer == NULL || *s_buffer == '\0') {
        return 0;
    }

    while (*pppp++ != NULL) {
        ++count;
    }

    return count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    size_t paragraph_count = get_total_paragraph_count();

    return paragraph_index < paragraph_count ? s_document[paragraph_index] : NULL;
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
    size_t i = 0;

    const char** start = *paragraph;
    const char** end_or_null;
    size_t count = 0;

    if (start == NULL) {
        return 0;
    }

    while (s_document[i] != paragraph) {
        ++i;
    }
    
    end_or_null = s_document[i + 1] == NULL ? NULL : *s_document[i + 1];

    while ((end_or_null != NULL && start < end_or_null) || (end_or_null == NULL && *start != NULL)) {
        ++start;
        ++count;
    }

    return count;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
    size_t i = 0;
    const char*** start = paragraph;
    const char*** end_or_null;
    size_t count = 0;

    if (start == NULL) {
        return 0;
    }

    while (s_document[i] != paragraph) {
        ++i;
    }

    end_or_null = s_document[i + 1];

    while ((end_or_null != NULL && start < end_or_null) || (end_or_null == NULL && *start != NULL)) {
        ++start;
        ++count;
    }

    return count;
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
    size_t sentence_count;
    const char*** paragraph = get_paragraph_or_null(paragraph_index);

    if (paragraph == NULL) {
        return NULL;
    }

    sentence_count = get_paragraph_sentence_count(paragraph);

    if (sentence_index >= sentence_count) {
        return NULL;
    }

    return paragraph[sentence_index];
}

unsigned int get_sentence_word_count(const char** sentence)
{
    const char** start = sentence;
    const char** end_or_null;
    size_t i = 0;
    size_t count = 0;

    if (start == NULL) {
        return 0;
    }

    while (s_paragraph[i++] != sentence) {
    }

    end_or_null = s_paragraph[i];

    while ((end_or_null != NULL && start < end_or_null) || (end_or_null == NULL && *start != NULL)) {
        ++start;
        ++count;
    }

    return count;
}

int print_as_tree(const char* filename)
{
    const char* pa = "Paragraph ";
    const char* se = "Sentence ";
    const char* tap = "    ";

    size_t paragraph_count;
    size_t sentence_count;
    size_t word_count;

    size_t i;
    size_t j;
    size_t k;

    FILE* stream;

    if (s_buffer == NULL) {
        return FALSE;
    }

    stream = fopen(filename, "w");

    if (stream == NULL) {
        return FALSE;
    }

    paragraph_count = get_total_paragraph_count();

    for (i = 0; i < paragraph_count; ++i) {
        sentence_count = get_paragraph_sentence_count(s_document[i]);
        fprintf(stream, "%s", pa);
        fprintf(stream, "%d:\n", i);

        for (j = 0; j < sentence_count; ++j) {
            word_count = get_sentence_word_count(s_document[i][j]);
            fprintf(stream, "%s%s", tap, se);
            fprintf(stream, "%d:\n", j);

            for (k = 0; k < word_count; ++k) {
                if (i == paragraph_count - 1 && j == sentence_count - 1 && k == word_count - 1) {
                    fprintf(stream, "%s%s", tap, tap);
                    fprintf(stream, "%s", s_document[i][j][k]);
                    goto exit;
                }
                fprintf(stream, "%s%s", tap, tap);
                fprintf(stream, "%s\n", s_document[i][j][k]);
            }
        }
        fprintf(stream, "\n");
    }

exit:
    fclose(stream);

    return TRUE;
}


            
    

