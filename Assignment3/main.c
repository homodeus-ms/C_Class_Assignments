#include "document_analyzer.h"

int main(void)
{
    const char** sentence = NULL;
    const char*** paragraph = NULL;
    unsigned int i = 0U;
    unsigned int j = 0U;

    assert(load_document("data/doesntexist.txt") == FALSE);
    assert(load_document("data/test.txt") == TRUE);

    printf("total_word : %d\n", get_total_word_count());
    printf("total_sent : %d\n", get_total_sentence_count());
    printf("total_para : %d\n", get_total_paragraph_count());

    printf("\n");

    paragraph = get_paragraph_or_null(0);
    
    printf("parpa_word_count : %d\n", get_paragraph_word_count(paragraph));
    printf("para_sent_count : %d\n\n", get_paragraph_sentence_count(paragraph));

    printf("%s\n", paragraph[0][0]);
    printf("%s\n", paragraph[0][1]);


    assert(print_as_tree("data/test_output.txt") == TRUE);


    dispose();


    printf("NO ASSERT!");

    return 0;
}
