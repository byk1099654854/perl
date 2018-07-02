#include "perl_num_ip.h"

#include <hs/hs.h>
#include "gtest/gtest.h"

static int EventHandler(unsigned int id, unsigned long long from,
                        unsigned long long to, unsigned int flags, void *ctx) {
  /* printf("Match for pattern \"%s\" at offset %llu\n", (char *)ctx, to); */
  /* *(int*)ctx = 0; */
  *static_cast<int*>(ctx) = 0;
  return 0;
}

int TestIPOpenOpen(const string& ip, const string& ip_left,
                   const string& ip_right) {
  string perl = GetPerlIpOpenOpen(ip_left, ip_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL, &database,
                 &compile_err) != HS_SUCCESS) {
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += ip;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

int TestIPOpenClose(const string& ip, const string& ip_left,
                    const string& ip_right) {
  string perl = GetPerlIpOpenClose(ip_left, ip_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL,
                 &database, &compile_err) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            pattern.c_str(), compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += ip;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS) {
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

int TestIPCloseOpen(const string& ip, const string& ip_left,
                    const string& ip_right) {
  string perl = GetPerlIpCloseOpen(ip_left, ip_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL,
                 &database, &compile_err) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            pattern.c_str(), compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += ip;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS ) {
    fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

int TestIPCloseClose(const string& ip, const string& ip_left,
                     const string& ip_right) {
  string perl = GetPerlIpCloseClose(ip_left, ip_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL,
                  &database, &compile_err) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            pattern.c_str(), compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += ip;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

int TestNumOpenOpen(const string& num, const string& num_left,
                    const string& num_right) {
  string perl = GetPerlOpenOpen(num_left, num_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL,
                 &database, &compile_err) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            pattern.c_str(), compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += num;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

int TestNumOpenClose(const string& num, const string& num_left,
                     const string& num_right) {
  string perl = GetPerlOpenClose(num_left, num_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL,
                 &database, &compile_err) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            pattern.c_str(), compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += num;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

int TestNumCloseOpen(const string& num, const string& num_left,
                     const string& num_right) {
  string perl = GetPerlCloseOpen(num_left, num_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL,
                 &database, &compile_err) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            pattern.c_str(), compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += num;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

int TestNumCloseClose(const string& num, const string& num_left,
                      const string& num_right) {
  string perl = GetPerlCloseClose(num_left, num_right);
  if (0 == perl.length()) {
    return -1;
  }
  string pattern = "\"(";
  pattern += perl;
  pattern += ")\"";
  hs_database_t *database;
  hs_compile_error_t *compile_err;
  if (hs_compile(pattern.c_str(), HS_FLAG_DOTALL, HS_MODE_BLOCK, NULL,
                 &database, &compile_err) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to compile pattern \"%s\": %s\n",
            pattern.c_str(), compile_err->message);
    hs_free_compile_error(compile_err);
    return -1;
  }
  string data = "\"";
  data += num;
  data += "\"";
  int ret = -1;
  hs_scratch_t *scratch = NULL;
  if (hs_alloc_scratch(database, &scratch) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to allocate scratch space. Exiting.\n");
    hs_free_database(database);
    return -1;
  }
  unsigned int length = data.length();
  if (hs_scan(database, data.c_str(), length, 0, scratch, EventHandler,
              &ret) != HS_SUCCESS) {
    fprintf(stderr, "ERROR: Unable to scan input buffer. Exiting.\n");
    hs_free_scratch(scratch);
    hs_free_database(database);
    return -1;
  }
  hs_free_scratch(scratch);
  hs_free_database(database);
  return ret;
}

/* 测试4种情况他们的参数和期望返回值是一样时使用 */
void TestIpArgumentRetSame(const int& ret, const string& ip, const string& ip_left,
                           const string& ip_right) {
  ASSERT_EQ(ret, TestIPOpenOpen(ip, ip_left, ip_right));
  ASSERT_EQ(ret, TestIPOpenClose(ip, ip_left, ip_right));
  ASSERT_EQ(ret, TestIPCloseOpen(ip, ip_left, ip_right));
  ASSERT_EQ(ret, TestIPCloseClose(ip, ip_left, ip_right));
}

void TestIp() {
  printf("--192.1.18.29--192.1.18.12-\n");
  ASSERT_EQ(-1, TestIPOpenOpen("192.1.18.29", "192.1.18.29", "192.1.18.12"));
  ASSERT_EQ(0, TestIPOpenClose("192.1.18.29", "192.1.18.29", "192.1.18.12"));
  ASSERT_EQ(-1, TestIPCloseOpen("192.1.18.29", "192.1.18.29", "192.1.18.12"));
  ASSERT_EQ(0, TestIPCloseClose("192.1.18.29", "192.1.18.29", "192.1.18.12"));
  ASSERT_EQ(-1, TestIPOpenOpen("192.1.18.12", "192.1.18.29", "192.1.18.12"));
  ASSERT_EQ(-1, TestIPOpenClose("192.1.18.12", "192.1.18.29", "192.1.18.12"));
  ASSERT_EQ(0, TestIPCloseOpen("192.1.18.12", "192.1.18.29", "192.1.18.12"));
  ASSERT_EQ(0, TestIPCloseClose("192.1.18.12", "192.1.18.29", "192.1.18.12"));
  long i = 0;
  for (i = 13; i < 29; i++) {
    char ip[20] = {0};
    sprintf(ip, "192.1.18.%d", i);
    TestIpArgumentRetSame (0, ip, "192.1.18.29", "192.1.18.12");
  }
  printf("--182.16.1.2---192.168.18.19-\n");
  for (i = 19; i < 256; i++) {
    char ip[20] = {0};
    sprintf(ip, "182.16.1.%d", i);
    TestIpArgumentRetSame (0, ip, "182.16.1.2", "192.168.18.19");
  }
  int k = 0;
  for (i = 20; i < 256; i++) {
    for (k = 0; k < 256; k++) {
      char ip[20] = {0};
      sprintf(ip, "182.%d.%d.5", i, k);
      TestIpArgumentRetSame(0, ip, "182.16.1.2", "192.168.18.19");
    }
  }
  for (i = 183; i < 191; i++) {
    for (k = 0; k < 256; k++) {
      char ip[20] = {0};
      sprintf(ip, "%d.%d.123.5", i, k);
      TestIpArgumentRetSame (0, ip, "182.16.1.2", "192.168.18.19");
    }
  }
}

void TestNum() {
  printf("----11111---11111-\n");
  ASSERT_EQ(-1, TestNumOpenOpen("11111", "11111", "11111"));
  ASSERT_EQ(-1, TestNumOpenClose("11111", "11111", "11111"));
  ASSERT_EQ(-1, TestNumCloseOpen("11111", "11111", "11111"));
  ASSERT_EQ(0, TestNumCloseClose("11111", "11111", "11111"));
  printf("---34837---34838--\n");
  ASSERT_EQ(-1, TestNumOpenOpen("34837", "34837", "34838"));
  ASSERT_EQ(-1, TestNumOpenClose("34837", "34837", "34838"));
  ASSERT_EQ(0, TestNumCloseOpen("34837", "34837", "34838"));
  ASSERT_EQ(0, TestNumCloseClose("34837", "34837", "34838"));
  ASSERT_EQ(-1, TestNumOpenOpen("34838", "34837", "34838"));
  ASSERT_EQ(0, TestNumOpenClose("34838", "34837", "34838"));
  ASSERT_EQ(-1, TestNumCloseOpen("34838", "34837", "34838"));
  ASSERT_EQ(0, TestNumCloseClose("34838", "34837", "34838"));
  printf("-99999----100000---\n");
  ASSERT_EQ(-1, TestNumOpenOpen("99999", "100000", "99999"));
  ASSERT_EQ(-1, TestNumOpenClose("99999", "100000", "99999"));
  ASSERT_EQ(0, TestNumCloseOpen("99999", "100000", "99999"));
  ASSERT_EQ(0, TestNumCloseClose("99999", "100000", "99999"));
  ASSERT_EQ(-1, TestNumOpenOpen("100000", "100000", "99999"));
  ASSERT_EQ(0, TestNumOpenClose("100000", "100000", "99999"));
  ASSERT_EQ(-1, TestNumCloseOpen("100000", "100000", "99999"));
  ASSERT_EQ(0, TestNumCloseClose("100000", "100000", "99999"));
  printf("-114-----23074--\n");
  long i = 0;
  for (i = 115; i < 23074; i++) {
    char num[20] = {0};
    sprintf(num, "%d", i);
    ASSERT_EQ(0, TestNumOpenOpen(num, "114", "23074"));
    ASSERT_EQ(0, TestNumOpenClose(num, "114", "23074"));
    ASSERT_EQ(0, TestNumCloseOpen(num, "114", "23074"));
    ASSERT_EQ(0, TestNumCloseClose(num, "114", "23074"));
  }
}

TEST(test_ip, test){
  TestIp();
  TestNum();
}

int main(int argc, char *argv[]){

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}