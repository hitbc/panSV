/* sub_example.c libabpoa usage example
   To compile:
      gcc -O2 sub_example.c -I ./include -L ./lib -labpoa -lz -o sub_example
  Or: gcc -O2 sub_example.c -I ./include ./lib/libabpoa.a -lz -o sub_example
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "abpoa.h"

// AaCcGgTtNn ==> 0,1,2,3,4
unsigned char _nt4_table[256] = {
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 5 /*'-'*/, 4, 4,
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 0, 4, 1,  4, 4, 4, 2,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  3, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 0, 4, 1,  4, 4, 4, 2,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  3, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4, 
	4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4,  4, 4, 4, 4
};

int main_abPOA(void) {
    int i, j, n_seqs = 7;
    char seqs[100][1000] = {

        };

    int beg_end_id[100][2] = {

    };

    // initialize variables
    abpoa_t *ab = abpoa_init();
    abpoa_para_t *abpt = abpoa_init_para();
   // abpt->align_mode = 2;
    //abpt->align_mode = 1;
//    abpt->wb = -1;
//    abpt->wf = -1;
//    abpt->zdrop = 10;
//    abpt->end_bonus = 10;
    //abpt->cons_agrm = 0;

//    abpt->match = 1;
//    abpt->mismatch = 4;
//    abpt->gap_open1 = 10;
//    abpt->gap_open2 = 24;
//    abpt->gap_ext1 = 4;
//    abpt->gap_ext2 = 4;

    // alignment parameters
    // abpt->align_mode = 0; // 0:global alignment, 1:extension
    // abpt->match = 2;      // match score
    // abpt->mismatch = 4;   // mismatch penalty
    // abpt->gap_mode = ABPOA_CONVEX_GAP; // gap penalty mode
    // abpt->gap_open1 = 4;  // gap open penalty #1
    // abpt->gap_ext1 = 2;   // gap extension penalty #1
    // abpt->gap_open2 = 24; // gap open penalty #2
    // abpt->gap_ext2 = 1;   // gap extension penalty #2
                             // gap_penalty = min{gap_open1 + gap_len * gap_ext1, gap_open2 + gap_len * gap_ext2}
    // abpt->bw = 10;        // extra band used in adaptive banded DP
    // abpt->bf = 0.01; 
     
    // output options
    abpt->out_msa = 1; // generate Row-Column multiple sequence alignment(RC-MSA), set 0 to disable
    abpt->out_cons = 1; // generate consensus sequence, set 0 to disable
   // abpt->cons_agrm = 2;
    abpoa_post_set_para(abpt);
    //abpt->cons_agrm = 2;
    // collect sequence length, trasform ACGT to 0123
    int *seq_lens = (int*)malloc(sizeof(int) * n_seqs);
    uint8_t **bseqs = (uint8_t**)malloc(sizeof(uint8_t*) * n_seqs);
    for (i = 0; i < n_seqs; ++i) {
        seq_lens[i] = strlen(seqs[i]);
        bseqs[i] = (uint8_t*)malloc(sizeof(uint8_t) * seq_lens[i]);
        for (j = 0; j < seq_lens[i]; ++j)
            bseqs[i][j] = _nt4_table[(int)seqs[i][j]];
    }

    // perform abpoa-msa
    ab->abs->n_seq = n_seqs;
    abpoa_res_t res;
    for (i = 0; i < n_seqs; ++i) {
        res.graph_cigar = 0, res.n_cigar = 0; res.is_rc = 0;
        abpoa_align_sequence_to_subgraph(ab, abpt, beg_end_id[i][0], beg_end_id[i][1], bseqs[i], seq_lens[i], &res);
        int exc_beg, exc_end;
        if (i != 0) abpoa_subgraph_nodes(ab, beg_end_id[i][0], beg_end_id[i][1], &exc_beg, &exc_end);
        else exc_beg = 0, exc_end = 0;
        abpoa_add_subgraph_alignment(ab, abpt, exc_beg, exc_end, bseqs[i], seq_lens[i], res, i, n_seqs);
        if (res.n_cigar) free(res.graph_cigar);
    }
    if (abpt->out_cons) {
        abpoa_generate_consensus(ab, abpt, stdout, NULL, NULL, NULL, NULL);
        if (ab->abg->is_called_cons == 0)
            fprintf(stderr, "Warning: no consensus sequence generated.\n");
    }
    if (abpt->out_msa) {
        abpoa_generate_rc_msa(ab, abpt, stdout, NULL, NULL);
    }
    // abpoa_reset_graph(ab, abpt, seq_lens[0]); // reset graph before re-use

    /* generate DOT partial order graph plot */
   // abpt->out_pog = strdup("sub_example.png"); // dump parital order graph to file
    //if (abpt->out_pog != NULL) abpoa_dump_pog(ab, abpt);
    for (i = 0; i < n_seqs; ++i) free(bseqs[i]);
    free(bseqs); free(seq_lens);
    abpoa_free(ab); abpoa_free_para(abpt);
    return 0;
}
