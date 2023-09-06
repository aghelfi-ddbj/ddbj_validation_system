# ddbj_validation_system
Designed and Developed an Automated Validation System for Diverse Submission File Types

Eukarya/ Prokarya (DDBJ_mss_validation, SVP and DDBJ_autofix): Overview
---
DFAST出力以外のファイルとDFASTのファイル（原核生物・真核生物ゲノム）に対しては以下のツールを使用する。ファイルの問題点を検出することとファイルの修正機能を連続的に実行可能。<br>
DBLINKにBioSampleが記載されている必要がある。<br>

![ag_packages_20220415_overview](https://user-images.githubusercontent.com/85154564/164154159-0132296e-e0af-4428-88ed-a7569183068b.jpg)

Command lines on supercom (It is NOT required to type module R):<br><br>

Step 1: [ddbj_mss_validation](https://github.com/ddbj/annotator/tree/master/aghelfi/ddbj_mss_validation). BIOSAMPLE IS MANDATORY!<br>

```
sh /home/andrea/scripts/ddbj_mss_validation
```
Step 2: [ddbj_autofix](https://github.com/ddbj/annotator/tree/master/aghelfi/ddbj_autofix). BIOSAMPLE IS MANDATORY!<br>

```
sh /home/andrea/scripts/ddbj_autofix
```
#### SVP - Sequence Validator Prototypeの機能も含める

![ag_packages_202204_svp](https://user-images.githubusercontent.com/85154564/162892863-fcec0d7c-4826-4acc-aa3d-75938a2c2312.jpg)


#### Common_checkの機能も含める (Annotation file - Common)

![common_CMC0202](https://user-images.githubusercontent.com/85154564/197689448-5869743a-4c4b-43e4-89b3-3ab859864c4b.png)

#### Automated File Type Detection

![ag_packages_202301_ddbj_filetype](https://user-images.githubusercontent.com/85154564/214238619-017e4d16-c848-42a9-ac87-4e9c334f8a9a.jpg)


[ddbj_file_type](https://github.com/ddbj/annotator/tree/master/aghelfi/detect_file_type)
```
sh /home/andrea/scripts/ddbj_filetype
```

Eukarya/ Prokarya (DDBJ_mss_validation, SVP and DDBJ_autofix): Detailed information
---
Works on supercomputer nodes. <br><br>

Step 1. [ddbj_mss_validation](https://github.com/ddbj/annotator/tree/master/aghelfi/ddbj_mss_validation) run step A then run in parallel steps B to F:<br><br>
A. [format_files](https://github.com/ddbj/annotator/tree/master/aghelfi/format_files)<br>
B. [mss_validation](https://github.com/ddbj/annotator/tree/master/aghelfi/mss_validation)<br>
C. [common_check](https://github.com/ddbj/annotator/tree/master/aghelfi/common_check)<br>
D. [svp](https://github.com/ddbj/annotator/tree/master/aghelfi/sequence_validator_prototype)<br>
E. [ag_jParser_transChecker](https://github.com/ddbj/annotator/tree/master/aghelfi/nkf_jParser_transChecker)<br>
F. [check output jParser_transChecker](https://github.com/ddbj/annotator/tree/master/aghelfi/nkf_jParser_transChecker)<br>

```
# supercom
sh /home/andrea/scripts/ddbj_mss_validation
```
<pre>
実行後に生成されるファイルと設置されるディレクトり
例：作業ディレクトリ
/mass-data/mass-id/yyyymmdd
annotation file: tokido-0001.ann
sequence file:   tokido-0001.fasta

・ddbj_mss_validationを実行後
/mass-data/mass-id/yyyymmdd/Rfixed
confirmation_report.tsv:biosampleとアノテーションファイル間で記述の違いを表示
curators_report.tsv：修正するqualifierの個所数のまとめ

/mass-data/mass-id/yyyymmdd/out_jParser
tokido-0001.txt：jParserのログファイル
/mass-data/mass-id/yyyymmdd/out_tranChecker
AA_seq_tokido-0001.faa: アミノ酸配列
transl_error_tokido-0001: transChckerのログ

・SVP - Sequence Validator Prototypeを実行後
/mass-data/mass-id/yyyymmdd/
warnings_SVP.tsv: SVPの実行ログ。
/mass-data/mass-id/yyyymmdd/Rfixed
tokido-0001.fasta：終端子が追加された配列ファイル

</pre>
Step 3. [ddbj_autofix](https://github.com/ddbj/annotator/tree/master/aghelfi/ddbj_autofix): ファイルの修正 (gap overlap, locus_tag, country, organism, strain, isolate, cultivar, bioproject, collection_date, host and subspecies)<br>
```
# supercom
sh /home/andrea/scripts/ddbj_autofix
```
<pre>
・ddbj_autofixを実行
実行時には、以下のファイルを参照して修正を実行する
/mass-data/mass-id/yyyymmdd/Rfixed
confirmation_report.tsv

実行後に生成されるファイル
/mass-data/mass-id/yyyymmdd/Rfixed
tokido-0001.ann:修正後のアノテーションファイル
tokido-0001.fasta：終端子が追加された配列ファイル <-- SVP実行後のファイル
</pre>

