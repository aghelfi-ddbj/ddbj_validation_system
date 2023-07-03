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
Step 3: [ddbj_sakura2DB](https://github.com/ddbj/annotator/tree/master/aghelfi/sakura2DB)<br> 

ATTENTION: There must be only one type of data for each directory, otherwise the system will be suspended.

Data types implemented on the current version (WGS, TLS, TPA-WGS, TPA-TSA, TPA-assembly, ENV, TSA, MAGs-Complete genome, Complete genome, Complete genome phage, Complete genome virus, Complete genome organelle, General). If filetype is not automatically detected the system will ask for curators to input correct prefix, it is under development to set the hostname. Also set_id (version) was implemented when it applies.
```
sh /home/andrea/scripts/ddbj_sakura2DB
```
If WGS and prefix were already assigned on -test. Please, use the following command line for the second run.
```
sh /home/andrea/scripts/ddbj_sakura2DB_2nd_run
```
Step 4: <br><br>
[ddbj_kaeru](https://github.com/ddbj/annotator/tree/master/aghelfi/ddbj_kaeru)<br> 
- Automatically update MSS Working List (submissions)
- Then automatically move workdir to DONE
- Automatically creates "disable-upload" file in w3const
```
sh /home/andrea/scripts/ddbj_kaeru
```
OR <br><br>
[ddbj_kaeru4old](https://github.com/ddbj/annotator/tree/master/aghelfi/ddbj_kaeru4old)<br>
- Automatically update MSS Working List (作業履歴管理): total_entry, accession, prefix_count, BioProject, BioSample, DRR
- Automatically move workdir to DONE
```
sh /home/andrea/scripts/ddbj_kaeru4old
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
Works on supercomputer nodes and ddbjs1. <br><br>

Step 1. [ddbj_mss_validation](https://github.com/ddbj/annotator/tree/master/aghelfi/ddbj_mss_validation) run step A then run in parallel steps B to F:<br><br>
A. [format_files](https://github.com/ddbj/annotator/tree/master/aghelfi/format_files)<br>
B. [mss_validation](https://github.com/ddbj/annotator/tree/master/aghelfi/mss_validation)<br>
C. [common_check](https://github.com/ddbj/annotator/tree/master/aghelfi/common_check)<br>
D. [svp](https://github.com/ddbj/annotator/tree/master/aghelfi/sequence_validator_prototype)<br>
E. [ag_jParser_transChecker](https://github.com/ddbj/annotator/tree/master/aghelfi/nkf_jParser_transChecker)<br>
F. [check output jParser_transChecker](https://github.com/ddbj/annotator/tree/master/aghelfi/nkf_jParser_transChecker)<br>

```
# supercom
# It is NOT required to type module R
sh /home/andrea/scripts/ddbj_mss_validation

# ddbjs1
sh /home/andreaghelfi/backup_data_gw/scripts/ddbj_mss_validation
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

# ddbjs1
sh /home/andreaghelfi/backup_data_gw/scripts/ddbj_autofix
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

### Background tables update (Nano-tsunami)

![ag_packages_20211210_nano-tsunami](https://user-images.githubusercontent.com/85154564/145515517-4e62f81f-ffeb-4e56-b156-ba907a7e1e35.jpg)


(Extra) [nano-tsunami](https://github.com/ddbj/annotator/tree/master/aghelfi/update_tables_metadata): automated tables update - [crontab](https://ddbj-dev.atlassian.net/wiki/spaces/curators/pages/1988591629/Nano-Tsunami+Preparations+of+tables+required+to+run+Rvalidator+ddbj+mss+validation+and+ddbj+autofix). <br>
##### Update the background tables every hour, by automatically accessing BioSample, BioProject and drmdb, but if BioSample were updated by curators, please run the following command line, in any directory, on ddbjs1 to instantly (less than 1 minute) update nano-tsunami.
```
sh /home/andreaghelfi/backup_data_gw/scripts/update_tables
```
### Tools implemented on ddbj_mss_validation and/or ddbj_autofix
1. [format_and_clean_files](https://github.com/ddbj/annotator/tree/master/aghelfi/format_files): Check and convert files from windows format to linux, remove blank spaces and misplaced tabs.<br>
```
# supercom
sh /home/andrea/scripts/formatlinux_remove-blankspaces.sh

# ddbjs1
sh /home/andreaghelfi/backup_data_gw/scripts/formatlinux_remove-blankspaces.sh
```

2. [jParser_transChecker](https://github.com/ddbj/annotator/tree/master/aghelfi/nkf_jParser_transChecker): runs jParser and transChecker recursively. <br>
```
# supercom
sh /home/andrea/scripts/ag_jParser_transChecker.sh

# ddbjs1
sh /home/andreaghelfi/backup_data_gw/scripts/ag_jParser_transChecker.sh
```

### Extra tools
1. [RNA_editing](https://github.com/ddbj/annotator/tree/master/aghelfi/RNA_editing): Check consistency between annotation and fasta files regarding RNA editing.<br>
```
#supercom
module load r/3.5.2
sh /home/andrea/scripts/svp_rna_editing.sh

# ddbjs1
sh /home/andreaghelfi/backup_data_gw/scripts/svp_rna_editing.sh
```

2. [unzip](https://github.com/ddbj/annotator/tree/master/aghelfi/format_files): unzip recursively many files at once.<br>
```
# supercom
sh /home/andrea/scripts/ag_unzip.sh

# ddbjs1
sh /home/andreaghelfi/backup_data_gw/scripts/ag_unzip.sh
```
3. [search_organism_name](https://github.com/ddbj/annotator/tree/master/aghelfi/update_tables_taxon_dump_files): search a list of organism names against the private taxonomy dump file.<br>
```
# supercom
# Input file name = organism.list
sh /home/andrea/scripts/search_organism_name.sh
```
<br>

### Tutorials and Presentations
2022.07.12
[ghelfi_presentation_20220715.pptx](https://github.com/ddbj/annotator/files/9088645/ghelfi_presentation_20220715.pptx)

2022.03.16
[ag_packages_20220316_presentation.pdf](https://github.com/ddbj/annotator/files/8258582/ag_packages_20220316_presentation.pdf)

2021.11.17 
[ag_packages_20211117_tutorial.pdf](https://github.com/ddbj/annotator/files/7551844/ag_packages_20211117_tutorial.pdf)

2021.09.29 
[ag_packages_20210929.pdf](https://github.com/ddbj/annotator/files/7249474/ag_packages_20210929.pdf)

