#pragma once

// アニメーションキー(クォータニオン
struct KdAnimKeyQuaternion
{
	float				m_time = 0;		// 時間
	Math::Quaternion	m_quat;			// クォータニオンデータ
};

// アニメーションキー(ベクトル
struct KdAnimKeyVector3
{
	float				m_time = 0;		// 時間
	Math::Vector3		m_vec;			// 3Dベクトルデータ
};

//============================
// アニメーションデータ
//============================
struct KdAnimationData
{
	// アニメーション名
	std::string		m_name;
	// アニメの長さ
	float			m_maxLength = 0;

	// １ノードのアニメーションデータ
	struct Node
	{
		int			m_nodeOffset = -1;	// 対象モデルノードのOffset値

		// 各チャンネル
		std::vector<KdAnimKeyVector3>		m_translations;	// 位置キーリスト
		std::vector<KdAnimKeyQuaternion>	m_rotations;	// 回転キーリスト
		std::vector<KdAnimKeyVector3>		m_scales;		// 拡縮キーリスト

		// 現在のアニメーションの補間=============================================================================
		void Interpolate(Math::Matrix& rDst, float time );
		bool InterpolateTranslations(Math::Vector3& result, float time);
		bool InterpolateRotations(Math::Quaternion& result, float time);
		bool InterpolateScales(Math::Vector3& result, float time);

		// 次のアニメーションへの補間処理=========================================================================
		void NextAnimationInterpolate(Math::Matrix& rDst, float time);
		bool NextAnimationInterpolateTranslations(Math::Vector3& result, const Math::Matrix prev, float time);
		bool NextAnimationInterpolateRotations(Math::Quaternion& result, const Math::Matrix prev, float time);
		bool NextAnimationInterpolateScales(Math::Vector3& result, const Math::Matrix prev,float time);
	};

	struct NextNode
	{
		std::vector<KdAnimKeyVector3>		m_translations;	// 位置キーリスト
		std::vector<KdAnimKeyQuaternion>	m_rotations;	// 回転キーリスト
		std::vector<KdAnimKeyVector3>		m_scales;		// 拡縮キーリスト

		// 次のアニメーションへの補間処理=========================================================================
		void NextAnimationInterpolate(Math::Matrix& rDst, float time);
		bool NextAnimationInterpolateTranslations(Math::Vector3& result, const Math::Matrix prev, float time);
		bool NextAnimationInterpolateRotations(Math::Quaternion& result, const Math::Matrix prev, float time);
		bool NextAnimationInterpolateScales(Math::Vector3& result, const Math::Matrix prev, float time);
	};

	// 全ノード用アニメーションデータ
	std::vector<Node>	m_nodes;
};

class KdAnimator
{
public:

	inline void SetAnimation(const std::shared_ptr<KdAnimationData>& rData, bool isLoop = true, bool firstAnime = false)
	{
		if (!firstAnime)
		{
			m_spAnimation = rData;
			m_isLoop = isLoop;

			m_time = 0.0f;

			m_spNextAnimation = m_spAnimation;
		}
		else
		{
			SetNextAnimation(rData, isLoop);
		}
	}

	// アニメーションが終了してる？
	bool IsAnimationEnd() const
	{
		if (m_spAnimation == nullptr) { return true; }
		if (m_time >= m_spAnimation->m_maxLength) { return true; }

		return false;
	}

	// 今アニメーションが始まってどのくらい？
	float AnimationTime() const
	{
		if (m_spAnimation == nullptr) { return 0.0f; }
		if (m_time >= m_spAnimation->m_maxLength) { return m_spAnimation->m_maxLength; }

		return m_time;
	}

	// アニメーションの更新
	void AdvanceTime( std::vector<KdModelWork::Node>& rNodes, float speed = 1.0f);


	// アニメーション切り替え補間用関数=======================================================================
	// アニメーションの切り替え
	void ChengeAnimation( std::vector<KdModelWork::Node>& rNodes, float speed = 1.0f);

	// 次のアニメーションの予約
	void SetNextAnimation(const std::shared_ptr<KdAnimationData>& rData, bool isLoop = true)
	{
		m_spNextAnimation = rData;

		m_nextIsLoop = isLoop;
		m_nextTime = 0.0f;
	}

private:

	// 現在のアニメーション===================================================================================
	std::shared_ptr<KdAnimationData>	m_spAnimation = nullptr;	// 再生するアニメーションデータ

	float m_time = 0.0f;

	bool m_isLoop = false;


	// 次のアニメーション=====================================================================================
	std::shared_ptr<KdAnimationData>	m_spNextAnimation = nullptr;// 次に再生するアニメーションデータ

	float m_nextTime = 0.0f;

	bool m_nextIsLoop = false;

	// アニメーションの移行のために必要な変数=================================================================
	float m_changeTime = 0.0f;
};