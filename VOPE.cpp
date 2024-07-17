#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>

char file_to_encrypto[100]; // 需要加密的文件路径及名称
char file_to_decrypto[100]; // 需要解密的文件路径及名称
char encrypted_file[50] = "VOPE已加密文件"; // 加密后的部分文件名
char decrypted_file[50] = "VOPE已解密文件"; // 解密后的部分文件名
char password[10]; // 用户输入的密码
char encrypted_filename[200]; //原始后缀名防储存丢失 
char temp; // 临时数据值 
unsigned int length; // 储存原文件长度

int encryption_count = 0; // 加密次数
int ready0 = 0; // 加密次数
int ready100 = 100; // 加密次数


// 加密函数
void encrypt_password(char* password, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < strlen(password); j++) {
            password[j] = password[j] + 1; // 简单加密，每次加1
        }
    }
}

void encrypto() {
    system("title 文件加密模式");
    printf("请输入或直接拖入您需要加密文件的完整路径：\n");
    scanf("%100s", file_to_encrypto); // 输入需加密文件的完整路径及名称

    FILE *fp1 = fopen(file_to_encrypto, "rb");
    if (fp1 == NULL) {
        printf("打开文件失败！请检查您的文件路径是否正确或者存在空格\n");
        return;
    }

    fseek(fp1, 0, SEEK_END);
    length = ftell(fp1);
    rewind(fp1);
    printf("建议包含大小写和数字，并在10位以上\n");
    printf("请输入您的加密密钥(建议超过10位，不能超过14位）：\n");
    scanf("%100s", password);

    encrypt_password(password, encryption_count); // 加密密钥

    system("title 加密中...(加密所需要的时间根据文件大小而定)");
    unsigned char* encrypted_data = (unsigned char*)malloc(length);
    if (encrypted_data == NULL) {
        printf("内存分配失败！\n");
        fclose(fp1);
        return;
    }

    // 读取整个文件并加密
    for (size_t i = 0; i < length; i++) {
        fread(&encrypted_data[i], sizeof(unsigned char), 1, fp1);
        encrypted_data[i] ^= password[i % strlen(password)]; // 使用循环异或
    }

    // 创建加密文件，并在文件名后加上原始文件扩展名
    strcpy(encrypted_filename, encrypted_file);
    strcat(encrypted_filename, strrchr(file_to_encrypto, '.'));

    FILE *fp2 = fopen(encrypted_filename, "wb");
    if (fp2 == NULL) {
        printf("创建加密文件失败！\n");
        free(encrypted_data);
        fclose(fp1);
        return;
    }

    // 写入加密数据
    fwrite(encrypted_data, sizeof(unsigned char), length, fp2);
    printf("加密成功！加密文件(%s)已保存到加解密器当前目录下\n", encrypted_filename);
    printf("请牢记您的加密密钥！\n");
    system("title 加密完成！已完成加密！！");
    free(encrypted_data);
    fclose(fp1);
    fclose(fp2);
    getchar();
    getchar();
}

void decrypto() {
    system("title 文件解密模式");
    printf("请输入或直接拖入您需要解密文件的完整路径：\n");
    scanf("%100s", file_to_decrypto); // 输入需要解密的文件路径及名称

    FILE *fp1 = fopen(file_to_decrypto, "rb");
    if (fp1 == NULL) {
        printf("打开文件失败！请检查您的文件路径是否正确或者存在空格\n");
        return;
    }

    fseek(fp1, 0, SEEK_END);
    length = ftell(fp1);
    rewind(fp1);

    printf("请输入您的加密时输入的密钥：\n");
    scanf("%100s", password);

    // 解密密钥
    encrypt_password(password, encryption_count); // 解密密钥，这里假设加密和解密使用相同的算法

    system("title 解密中...(解密所需要的时间根据文件大小而定)");
    unsigned char* decrypted_data = (unsigned char*)malloc(length);
    if (decrypted_data == NULL) {
        printf("内存分配失败！\n");
        fclose(fp1);
        return;
    }

    // 读取加密文件并解密
    for (size_t i = 0; i < length; i++) {
        fread(&decrypted_data[i], sizeof(unsigned char), 1, fp1);
        decrypted_data[i] ^= password[i % strlen(password)]; // 使用循环异或
    }

    // 创建解密文件，并在文件名后加上原始文件扩展名
    char decrypted_filename[200];
    strcpy(decrypted_filename, decrypted_file);
    strcat(decrypted_filename, strrchr(file_to_decrypto, '.'));

    FILE *fp2 = fopen(decrypted_filename, "wb");
    if (fp2 == NULL) {
        printf("创建解密文件失败！\n");
        free(decrypted_data);
        fclose(fp1);
        return;
    }

    // 写入解密数据
    fwrite(decrypted_data, sizeof(unsigned char), length, fp2);
    printf("已按照密钥规律解密成功！解密文件(%s)已保存到加解密器当前目录下\n", decrypted_filename);
    system("title 解密完成！已按照密钥规律解密成功！");
    free(decrypted_data);
    fclose(fp1);
    fclose(fp2);
    getchar();
    getchar();
}

void set_encryption_1() {
    system("cls");
    system("title 设置密钥转换");
    printf("==============================================================\n");
    printf("密钥转换是在输入密钥后转换密钥，再使用转换的密钥加密文件\n");
    printf("转换方法是将密钥从大小写和数字以及标点符号转换到乱码\n");
    printf("转换次数为0可以关闭密钥转换\n");
    printf("加密器每次打开默认关闭密钥加密\n");
    printf("注意！过大的密钥加密次数可能导致导致加解密失败！\n");
    printf("注意！只有加密密钥次数和密钥同时相同，文件才会被正确解密！\n");
    printf("现在设定的转换次数: %d\n", encryption_count);
    printf("==============================================================\n");
    printf("请输入密钥次数：\n");
    scanf("%d", &encryption_count);
}




void setup(){
		system("cls");
            system("title 高级设置");
            printf("==============================================================\n");
            printf("高级设置界面\n");
            printf("注意！在这个界面做的任何修改都将在程序重新启动后还原\n");
            printf("部分高级设置可以增强安全性，让加密更加安全\n");
			printf("但请在使修改功能时确保您能理解功能的作用\n");
			printf("在此页面输入错误的选项会直接回到主页面\n");
			printf("==============================================================\n");
            printf("1.返回主界面   2.设置密钥转换\n");
            printf("==============================================================\n");
            printf("请输入您的选择：\n");
                int sub_choice;
                scanf("%d", &sub_choice);
                // 清除缓冲区中的非数字字符
            	int c;
            	while ((c = getchar()) != '\n' && c != EOF);
        
                if (sub_choice == 1) {
					return;
                }
                if (sub_choice == 2) {
					set_encryption_1();
                }
                if (sub_choice == 3) {
				
                }
                if (sub_choice == 4) {
				
                }
				if (sub_choice == 5) {
				
                }
                if (sub_choice == 6) {
				
                }
                
setup();
}






int main() {
    int choice = 0;
    while (1) {
        system("color 1b");
        system("cls");
        printf("==============================================================\n");
        system("title 欢迎使用VOPE文件加解密器");
        printf("欢迎使用VOPE文件加密器！\n");
        printf("建议将文件压缩成压缩包再加密！\n");
        printf("不支持文件夹加密！\n");
        printf("需要加密的文件在加密后不会被删除，请手动删除，解密也相同\n");
        printf("==============================================================\n");
        printf("在加解密界面可直接拖入文件\n");
        printf("小部分格式的文件暂不支持加密！\n");
        printf("==============================================================\n");
        printf("解密和加密的原理相同但不建议混淆使用！\n");
        printf("这可能导致数据永久无法恢复！\n");
        printf("需要加密的文件路径不能包含空格标点和特殊字符！中文可以\n");
        printf("==============================================================\n");
        printf("本程序在测试阶段，可能会出现各种难以言喻的错误\n");
        printf("==============================================================\n");
        printf("加密等级：中级\n");
        printf("==============================================================\n");
        printf("请输入您的选择\n");
        printf("1.加密文件   2.解密文件   3.退出主界面   4.高级设置\n");
        printf("==============================================================\n");
        if (scanf("%d", &choice) != 1) {
            // 清除缓冲区中的非数字字符
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        // 检查输入是否为有效选项
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
            printf("输入选择有误！请重新输入：\n");
            // 再次检查输入是否为数字
            if (scanf("%d", &choice) != 1) {
                // 清除缓冲区中的非数字字符
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }

        switch (choice) {
            case 1:
                encrypto();
                break;
            case 2:
                decrypto();
                break;
            case 3:
                printf("非常感谢您的使用！期待与您下次相见\n");
                return 0;
                break;
            case 4:
            	setup();
            	break;
        }
    }
    return 0;
}
