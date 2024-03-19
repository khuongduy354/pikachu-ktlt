Task: 2D array generation,  Keyboard Input, Visual, Save game.

# 2D array generation
- Quy ước Board `char** board` là mảng 2 chiều chứa char, các giá trị trong mảng như sau: 
' ' là ô trống 
'\0' là vật cản 
'A' là chữ cái (b c x y z j đó,....)  

- Đại loại mình cần 1 hàm để tạo mảng 2D chiều với config quy định trước 
- Các ô được tạo ngẫu nhiên nhưng mà phải đúng quy luật của config 
```cpp
struct GameConfig { 
  int m; 
  int n; 
  int distinct_chars; 
  int char_occurences[26]; // 26 chũ cái, mỗi ô là 1 số chẵn lần xuất hiện của chữ
}; 
int** generate_board(GameConfig config){}; //nghiên cứu chỗ này

int main(){  
  int char_occurences[26] = {...};
  GameConfigs default_config { 20, 20, 15, char_occurences } ; // 20x20, 15 chữ cái, với mảng gồm thông tin xuất hiện  

  int** board = generate_board(default_config); 
}
```

# Keyboard Input   
- Cái này thì tìm cách chạy chương trình, sao mà mình gõ 1 phím, thì nó nhận (có thể in ra để test) là đc    
- Search google có thể có.

# Visual  
- Vẽ (chủ yếu là cout sao cho đẹp) dựa theo cái mảng 2 chiều ở tren  
- Dùng thư viện để tô màu terminal (search google sẽ có), thích tô màu j tô
-> vẽ ở trên xog, cứ tô đại 1,2 ô, nó lên màu là hoàn thành. 

# Save game   
- Bây giờ cũng chưa biết lưu cái j nữa, thoi thì lưu cái struct config ở tren vô binary file là được  
- lưu theo format nào cũng được, xuống dòng, phẩy j đó,...


