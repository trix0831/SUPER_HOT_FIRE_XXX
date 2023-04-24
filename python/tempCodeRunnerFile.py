import sys

# 取得參數數量
n = len(sys.argv)
print("參數數量：", n - 1)

# 檢查參數數量
if n < 3:
    print("參數不足，至少需要 2 個參數。")
    sys.exit()

# 顯示所有參數
for i in sys.argv[1:]:
    print(i)