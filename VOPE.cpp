#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>

char file_to_encrypto[100]; // ��Ҫ���ܵ��ļ�·��������
char file_to_decrypto[100]; // ��Ҫ���ܵ��ļ�·��������
char encrypted_file[50] = "VOPE�Ѽ����ļ�"; // ���ܺ�Ĳ����ļ���
char decrypted_file[50] = "VOPE�ѽ����ļ�"; // ���ܺ�Ĳ����ļ���
char password[10]; // �û����������
char encrypted_filename[200]; //ԭʼ��׺�������涪ʧ 
char temp; // ��ʱ����ֵ 
unsigned int length; // ����ԭ�ļ�����

int encryption_count = 0; // ���ܴ���
int ready0 = 0; // ���ܴ���
int ready100 = 100; // ���ܴ���


// ���ܺ���
void encrypt_password(char* password, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < strlen(password); j++) {
            password[j] = password[j] + 1; // �򵥼��ܣ�ÿ�μ�1
        }
    }
}

void encrypto() {
    system("title �ļ�����ģʽ");
    printf("�������ֱ����������Ҫ�����ļ�������·����\n");
    scanf("%100s", file_to_encrypto); // ����������ļ�������·��������

    FILE *fp1 = fopen(file_to_encrypto, "rb");
    if (fp1 == NULL) {
        printf("���ļ�ʧ�ܣ����������ļ�·���Ƿ���ȷ���ߴ��ڿո�\n");
        return;
    }

    fseek(fp1, 0, SEEK_END);
    length = ftell(fp1);
    rewind(fp1);
    printf("���������Сд�����֣�����10λ����\n");
    printf("���������ļ�����Կ(���鳬��10λ�����ܳ���14λ����\n");
    scanf("%100s", password);

    encrypt_password(password, encryption_count); // ������Կ

    system("title ������...(��������Ҫ��ʱ������ļ���С����)");
    unsigned char* encrypted_data = (unsigned char*)malloc(length);
    if (encrypted_data == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        fclose(fp1);
        return;
    }

    // ��ȡ�����ļ�������
    for (size_t i = 0; i < length; i++) {
        fread(&encrypted_data[i], sizeof(unsigned char), 1, fp1);
        encrypted_data[i] ^= password[i % strlen(password)]; // ʹ��ѭ�����
    }

    // ���������ļ��������ļ��������ԭʼ�ļ���չ��
    strcpy(encrypted_filename, encrypted_file);
    strcat(encrypted_filename, strrchr(file_to_encrypto, '.'));

    FILE *fp2 = fopen(encrypted_filename, "wb");
    if (fp2 == NULL) {
        printf("���������ļ�ʧ�ܣ�\n");
        free(encrypted_data);
        fclose(fp1);
        return;
    }

    // д���������
    fwrite(encrypted_data, sizeof(unsigned char), length, fp2);
    printf("���ܳɹ��������ļ�(%s)�ѱ��浽�ӽ�������ǰĿ¼��\n", encrypted_filename);
    printf("���μ����ļ�����Կ��\n");
    system("title ������ɣ�����ɼ��ܣ���");
    free(encrypted_data);
    fclose(fp1);
    fclose(fp2);
    getchar();
    getchar();
}

void decrypto() {
    system("title �ļ�����ģʽ");
    printf("�������ֱ����������Ҫ�����ļ�������·����\n");
    scanf("%100s", file_to_decrypto); // ������Ҫ���ܵ��ļ�·��������

    FILE *fp1 = fopen(file_to_decrypto, "rb");
    if (fp1 == NULL) {
        printf("���ļ�ʧ�ܣ����������ļ�·���Ƿ���ȷ���ߴ��ڿո�\n");
        return;
    }

    fseek(fp1, 0, SEEK_END);
    length = ftell(fp1);
    rewind(fp1);

    printf("���������ļ���ʱ�������Կ��\n");
    scanf("%100s", password);

    // ������Կ
    encrypt_password(password, encryption_count); // ������Կ�����������ܺͽ���ʹ����ͬ���㷨

    system("title ������...(��������Ҫ��ʱ������ļ���С����)");
    unsigned char* decrypted_data = (unsigned char*)malloc(length);
    if (decrypted_data == NULL) {
        printf("�ڴ����ʧ�ܣ�\n");
        fclose(fp1);
        return;
    }

    // ��ȡ�����ļ�������
    for (size_t i = 0; i < length; i++) {
        fread(&decrypted_data[i], sizeof(unsigned char), 1, fp1);
        decrypted_data[i] ^= password[i % strlen(password)]; // ʹ��ѭ�����
    }

    // ���������ļ��������ļ��������ԭʼ�ļ���չ��
    char decrypted_filename[200];
    strcpy(decrypted_filename, decrypted_file);
    strcat(decrypted_filename, strrchr(file_to_decrypto, '.'));

    FILE *fp2 = fopen(decrypted_filename, "wb");
    if (fp2 == NULL) {
        printf("���������ļ�ʧ�ܣ�\n");
        free(decrypted_data);
        fclose(fp1);
        return;
    }

    // д���������
    fwrite(decrypted_data, sizeof(unsigned char), length, fp2);
    printf("�Ѱ�����Կ���ɽ��ܳɹ��������ļ�(%s)�ѱ��浽�ӽ�������ǰĿ¼��\n", decrypted_filename);
    system("title ������ɣ��Ѱ�����Կ���ɽ��ܳɹ���");
    free(decrypted_data);
    fclose(fp1);
    fclose(fp2);
    getchar();
    getchar();
}

void set_encryption_1() {
    system("cls");
    system("title ������Կת��");
    printf("==============================================================\n");
    printf("��Կת������������Կ��ת����Կ����ʹ��ת������Կ�����ļ�\n");
    printf("ת�������ǽ���Կ�Ӵ�Сд�������Լ�������ת��������\n");
    printf("ת������Ϊ0���Թر���Կת��\n");
    printf("������ÿ�δ�Ĭ�Ϲر���Կ����\n");
    printf("ע�⣡�������Կ���ܴ������ܵ��µ��¼ӽ���ʧ�ܣ�\n");
    printf("ע�⣡ֻ�м�����Կ��������Կͬʱ��ͬ���ļ��Żᱻ��ȷ���ܣ�\n");
    printf("�����趨��ת������: %d\n", encryption_count);
    printf("==============================================================\n");
    printf("��������Կ������\n");
    scanf("%d", &encryption_count);
}




void setup(){
		system("cls");
            system("title �߼�����");
            printf("==============================================================\n");
            printf("�߼����ý���\n");
            printf("ע�⣡��������������κ��޸Ķ����ڳ�������������ԭ\n");
            printf("���ָ߼����ÿ�����ǿ��ȫ�ԣ��ü��ܸ��Ӱ�ȫ\n");
			printf("������ʹ�޸Ĺ���ʱȷ��������⹦�ܵ�����\n");
			printf("�ڴ�ҳ����������ѡ���ֱ�ӻص���ҳ��\n");
			printf("==============================================================\n");
            printf("1.����������   2.������Կת��\n");
            printf("==============================================================\n");
            printf("����������ѡ��\n");
                int sub_choice;
                scanf("%d", &sub_choice);
                // ����������еķ������ַ�
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
        system("title ��ӭʹ��VOPE�ļ��ӽ�����");
        printf("��ӭʹ��VOPE�ļ���������\n");
        printf("���齫�ļ�ѹ����ѹ�����ټ��ܣ�\n");
        printf("��֧���ļ��м��ܣ�\n");
        printf("��Ҫ���ܵ��ļ��ڼ��ܺ󲻻ᱻɾ�������ֶ�ɾ��������Ҳ��ͬ\n");
        printf("==============================================================\n");
        printf("�ڼӽ��ܽ����ֱ�������ļ�\n");
        printf("С���ָ�ʽ���ļ��ݲ�֧�ּ��ܣ�\n");
        printf("==============================================================\n");
        printf("���ܺͼ��ܵ�ԭ����ͬ�����������ʹ�ã�\n");
        printf("����ܵ������������޷��ָ���\n");
        printf("��Ҫ���ܵ��ļ�·�����ܰ����ո���������ַ������Ŀ���\n");
        printf("==============================================================\n");
        printf("�������ڲ��Խ׶Σ����ܻ���ָ������������Ĵ���\n");
        printf("==============================================================\n");
        printf("���ܵȼ����м�\n");
        printf("==============================================================\n");
        printf("����������ѡ��\n");
        printf("1.�����ļ�   2.�����ļ�   3.�˳�������   4.�߼�����\n");
        printf("==============================================================\n");
        if (scanf("%d", &choice) != 1) {
            // ����������еķ������ַ�
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        // ��������Ƿ�Ϊ��Чѡ��
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
            printf("����ѡ���������������룺\n");
            // �ٴμ�������Ƿ�Ϊ����
            if (scanf("%d", &choice) != 1) {
                // ����������еķ������ַ�
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
                printf("�ǳ���л����ʹ�ã��ڴ������´����\n");
                return 0;
                break;
            case 4:
            	setup();
            	break;
        }
    }
    return 0;
}
