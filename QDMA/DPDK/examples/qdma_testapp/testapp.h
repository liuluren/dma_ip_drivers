/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2017-2018 Xilinx, Inc. All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define QDMA_MAX_PORTS	256

#define PORT_0 0

#define NUM_DESC_PER_RING 1024
#ifdef PERF_BENCHMARK
#define NUM_RX_PKTS (NUM_DESC_PER_RING - 2)
#else
#define NUM_RX_PKTS 32
#endif
#define MAX_NUM_QUEUES 2048
#define DEFAULT_NUM_QUEUES 64
#define RX_TX_MAX_RETRY			1000

#define MP_CACHE_SZ     512

#define MBUF_POOL_NAME_PORT   "mbuf_pool_%d"

/* User bar registers */
#define C2H_ST_QID_REG    0x0
#define C2H_ST_LEN_REG    0x4
#define C2H_CONTROL_REG              0x8
#define ST_LOOPBACK_EN               0x1
#define ST_C2H_START_VAL             0x2
#define ST_C2H_IMMEDIATE_DATA_EN     0x4
#define C2H_CONTROL_REG_MASK         0xF
#define H2C_CONTROL_REG    0xC
#define H2C_STATUS_REG    0x10
#define C2H_PACKET_COUNT_REG    0x20

extern int num_ports;

struct port_info {
	int config_bar_idx;
	int user_bar_idx;
	int bypass_bar_idx;
	unsigned int queue_base;
	unsigned int num_queues;
	unsigned int st_queues;
	unsigned int buff_size;
	char mem_pool[RTE_MEMPOOL_NAMESIZE];
};

extern struct port_info pinfo[QDMA_MAX_PORTS];
int port_init(int portid, int queue_base, int num_queues, int st_queues,
				int nb_descs, int buff_size);
int do_recv_st(int portid, int fd, int queueid, int input_size);
int do_recv_mm(int portid, int fd, int queueid, int size, int tot_num_desc);
int do_xmit(int portid, int fd, int queueid, int size, int nb_desc, int zbyte);
void load_file_cmds(struct cmdline *cl);
void port_close(int port_id);
void qdma_desc_dump(struct rte_eth_dev *dev, uint32_t qid);
void queue_context_dump(uint8_t bar_id, uint32_t qid, struct cmdline *cl);
int parse_cmdline(int argc, char **argv);
